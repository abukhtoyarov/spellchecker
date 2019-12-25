#pragma once
#include <sstream>
#include <list>
#include "bktree.hpp"

namespace spellchecker {

enum class State {
    correct,    // в словаре есть полное совпадение
    options,    // ошибка, есть возможные варианты исправления
    wrong,      // ошибка
    undefined,
};

template<class CharT> struct Result {
    // статус проверки
    State state_ = State::undefined;
    // информация о заменах
    std::vector<std::pair<int, std::basic_string<CharT>>> data_;
    // исследуемое слово
    std::basic_string<CharT> word_;
};

namespace details {

void delims(const char **d) { *d = " .,:-«»\"'!?@#%$^&*()"; }
void delims(const wchar_t **d) { *d = L" .,:-«»\"'!?@#%$^&*()"; }

}

template<class CharT> class Spellchecker {
public:
    Spellchecker() = default;

    //
    // Метод для загрузки словаря:
    // - слова с словаре должны быть перечислены через ' ', '\t' и '\n'
    // - перед добавлением слова с краев будут обрезаны символы " ,:\"'!?@#%$^&*()"
    // - перед добавлением слово будет приведено к нижнему регистру
    //
    void load(const std::basic_string<CharT> &str) {
        std::basic_stringstream<CharT> ss;
        ss << str;
        load(ss);
    }
    
    //
    // Метод для загрузки словаря:
    // - слова с словаре должны быть перечислены через ' ', '\t' и '\n'
    // - перед добавлением слова с краев будут обрезаны символы " ,:\"'!?@#%$^&*()"
    // - перед добавлением слово будет приведено к нижнему регистру
    // загрузка словаря [TODO] wchar specialization?
    //
    void load(std::basic_stringstream<CharT> &ss) {
        while(!ss.eof()) {
            std::basic_string<CharT> word;
            ss >> word;

            // нужно обрезать слово от всяких ненужных символов
            const CharT *delims = nullptr;
            details::delims(&delims);
            word = trim(word, delims);
            
            // нижний регистр
            word = to_lower(word);

            // [TODO] Добавить возможность перемещения в шаблон insert
            dic_.insert(std::move(word));
        }
    }

    //
    // Метод для проверки слов в строке.
    // - Принимаемая строка будет разделена на слова,
    // - будут убратны знаки препинания,
    // - будет убрано форматирование.
    //
    // Результат: состояние проверки и список возможных замен.
    //
    std::list<Result<CharT>> check(const std::basic_string<CharT> &words) {
        std::basic_stringstream<CharT> ss;
        ss << words;
        return check(ss);
    }
    
    //
    // Метод для проверки слов в строке.
    // - Принимаемая строка будет разделена на слова,
    // - будут убраны знаки препинания,
    // - будет убрано форматирование.
    //
    // Результат: состояние проверки и список возможных замен.
    //
    std::list<Result<CharT>> check(std::basic_stringstream<CharT> &ss) {
        std::list<Result<CharT>> results;
        while(!ss.eof()) {
            std::basic_string<CharT> word;
            ss >> word;

            // нужно обрезать слово от всяких ненужных символов
            const CharT *delims = nullptr;
            details::delims(&delims);
            word = trim(word, delims);
            
            // нижний регистр
            word = to_lower(word);

            auto opts = dic_.lookup(word, accuracy_);

            Result<CharT> result;
            result.word_ = word;

            if(!opts.empty()) {
                // сортировка по дистанции
                std::sort(std::begin(opts), std::end(opts), [] (const auto &l, const auto &r) { return l.first < r.first; });
                
                auto it = std::begin(opts);
                if(!(*it).first) {
                    // результат с полным совпадением
                    result.state_ = State::correct;
                    results.push_back(std::move(result));
                    continue;
                }

                result.state_ = State::options;

                // [TODO] Параметризировать количество выдаваемых результатов
                // Первые 5 результатов будет достаточно
                for(int i = 0; i < std::min(5, static_cast<int>(opts.size())); ++i, ++it) 
                    result.data_.emplace_back(it->first, it->second);
                results.push_back(std::move(result));
            } else {
                // 
                result.state_ = State::wrong;
                results.push_back(std::move(result));
            }
        }
        return results;
    }

    //
    // Сеттер для задания точности поиска в словаре (по-умолчанию: 1).
    //
    void accuracy(int accuracy) { accuracy_ = accuracy; }

    //
    // Геттер для получения значения точности поиска в словаре (по-умолчанию: 1).
    //
    int accuracy() { return accuracy_; }

protected:
    Spellchecker(Spellchecker &&) = delete;
    Spellchecker(const Spellchecker &) = delete;

private:
    // [TODO] Сейчас реализован только один алгоритм. Дальше возможно специализировать по алгоритму.
    bktree::Tree<CharT, levenshtein::Distance> dic_;
    int accuracy_ = 1;
};

}
