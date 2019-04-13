#pragma once 
#include <string>
#include <vector>

inline std::string to_lower(const std::string &str) {
    auto ret = str;
    std::transform(str.begin(), str.end(), ret.begin(), [] (unsigned char c) { return std::tolower(c); });
    return ret;
}

inline int distance(const std::string &l, const std::string &r) {
    auto lc = l.size() + 1;
    auto rc = r.size() + 1;

    // Матрица d содержит левенштейновские растояния между
    // первыми i символами строки l и 
    // первыми j символами строки r
    std::vector<int> d(lc * rc, 0);

    for(size_t i = 0; i < lc; ++i)
        d.at(i) = i;

    for(size_t j = 0; j < rc; ++j)
        d.at(j * lc) = j;

    for(size_t j = 1; j < rc; ++j) {
        for(size_t i = 1; i < lc; ++i) {
            int substitutionCost = l.at(i - 1) == r.at(j - 1) ? 0 : 1;
            d.at(lc * j + i) = std::min({
                d.at(lc * j + (i - 1)) + 1,                      // deletion
                d.at(lc * (j - 1) + i) + 1,                      // insertion
                d.at(lc * (j - 1) + (i - 1)) + substitutionCost  // substitution
            });
        }
    }
    return d.back();
}