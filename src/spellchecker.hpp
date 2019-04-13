#pragma once
#include <sstream>

#include "bktree.hpp"

namespace spellchecker {

class Spellchecker {
public:
    Spellchecker() = default;

    // загрузка словаря [TODO] wchar specialization?
    void load(const std::string &str) {
        std::stringstream ss;
        ss << str;
        load(ss);
    }

    void load(std::stringstream &ss) {
        while(!ss.eof()) {
            std::string word;
            ss >> word;

            // нужно обрезать слово от всяких ненужных символов
            word = trim(word, " ,:\"'!?@#%$^&*()");

            // [TODO] Добавить возможность перемещения в шаблон insert
            dic_.insert(std::move(word));
        }
    }

    // проверка текста
    std::string check(std::string &str) {
        std::stringstream ss;
        ss << str;
        return check(ss);
    }

    std::string check(std::stringstream &ss) {
        std::stringstream rs;
        while(!ss.eof()) {
            std::string word;
            ss >> word;

            // нужно обрезать слово от всяких ненужных символов
            word = trim(word, " ,:\"'!?@#%$^&*()");
            word = to_lower(word);
            
            // 
            auto results = dic_.lookup(word, 1);
            std::sort(std::begin(results), std::end(results), [] (const auto &l, const auto &r) { return l.first < r.first; });
            if(!results.empty()) {
                rs << results.front().second << " ";
            } else {
                rs << word;
            }
        }

        return rs.str();
    }


protected:
    Spellchecker(Spellchecker &&) = delete;
    Spellchecker(const Spellchecker &) = delete;

private:
    bktree::Tree<char, levenshtein::Distance> dic_;
};


}