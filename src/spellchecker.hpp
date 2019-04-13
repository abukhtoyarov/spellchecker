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

protected:
    Spellchecker(Spellchecker &&) = delete;
    Spellchecker(const Spellchecker &) = delete;

private:
    bktree::Tree<char, levenshtein::Distance> dic_;
};


}