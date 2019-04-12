#pragma once 
#include <string>
#include <vector>

// static debug data
// "hello", "Hell",     // delete
// "Hello", "hallo",    // replace
// "hello", "helloWEen" // insert

int distance(const std::string &l, const std::string &r) {
    auto lc = l.size() + 1;
    auto rc = r.size() + 1;

    // Матрица d содержит левенштейновские растояния между
    // первыми i символами строки l и 
    // первыми j символами строки r
    std::vector<int> d(lc * rc);

    for(size_t i = 0; i < lc; ++i)
        d.at(i) = i;

    for(size_t j = 0; j < rc; ++j)
        d.at(j * lc) = j;

    for(size_t j = 1; j < rc; ++j) {
        for(size_t i = 1; i < lc; ++i) {
            int substitutionCost = l.at(i) == r.at(j) ? 0 : 1;
            d.at(i * j) = std::min({
                d.at(i - 1 * j) + 1,                   // deletion
                d.at(i * j - 1) + 1,                   // insertion
                d.at(i - 1 * j - 1) + substitutionCost // substitution
            });
        }
    }
    return d.back();
}