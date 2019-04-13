#pragma once
#include <map>
#include "distance.hpp"

namespace bktree {

template<class CharT> struct Node {
    Node() = default;
    Node(const std::basic_string<CharT> &word) : word_(word) {}
    std::basic_string<CharT> word_;
    std::map<int, Node<CharT>> children_;

    // [TODO] Убрать рекурсию
    template<class DistanceAlg> void lookup(const std::basic_string<CharT> &word, int dist, std::vector<std::pair<int, std::basic_string<CharT>>> &result) const {
        auto d = distance<CharT, DistanceAlg>(word_, word);
            
        if(d <= dist) {
            // узел содержит дату, на интересной нам дистанции
            result.emplace_back(d, word_);
        }

        auto left = d - dist ? d - dist : 1;
        auto right = d + dist;
        
        for(const auto &n: children_) {
            if(left > n.first || right < n.first)
                continue;
            n.second.template lookup<DistanceAlg>(word, dist, result);
        }
    }
};

template<class CharT, class DistanceAlg>
class Tree {
    using NodeT = Node<CharT>;
public:
    Tree() = default;

    void insert(const std::basic_string<CharT> &word) {
        NodeT *current = &root_;
        
        while(true) {
            auto d = distance<CharT, DistanceAlg>(current->word_, word);
            if(!d) {
                // элемент существует
                break;
            }

            if(current->children_.empty()) {
                // можно добавлять элемент
                current->children_[d] = word;
                continue;
            }

            auto f = current->children_.find(d);
            if(std::end(current->children_) == f) {
                // на этой дистанции никого нет
                current->children_[d] = word;
                continue;
            }

            current = &f->second;
        }
        count_++;
    }

    size_t size() const { return count_; }

    std::vector<std::pair<int, std::basic_string<CharT>>> lookup(const std::basic_string<CharT> &word, int dist) {
        std::vector<std::pair<int, std::basic_string<CharT>>> result;
        root_.template lookup<DistanceAlg>(word, dist, result);
        return result;
    }

protected:
    Tree(Tree &&) = delete;
    Tree(const Tree &) = delete;

private:
    NodeT root_;
    size_t count_ = 0;
};


}