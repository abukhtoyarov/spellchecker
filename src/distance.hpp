#pragma once 
#include <string>
#include <vector>

//
// вместо дополнительного заголовка, будет лежать пока что здесь.
//
namespace details {

template<class CharT> int tolower(int c);
template<> int tolower<char>(int c) { return std::tolower(c); }
template<> int tolower<wchar_t>(int c) { return std::towlower(c); }

}

// преобразование строки к нижнему регистру
template<class CharT> inline std::basic_string<CharT> to_lower(const std::basic_string<CharT> &str) {
    auto ret = str;
    std::transform(str.begin(), str.end(), ret.begin(), [] (CharT c) { return details::tolower<CharT>(c); });
    return ret;
}

// trim from end of string (right)
template<class CharT> inline std::basic_string<CharT> &rtrim(std::basic_string<CharT> &s, const CharT *delims) {
    s.erase(s.find_last_not_of(delims) + 1);
    return s;
}

// trim from beginning of string (left)
template<class CharT> inline std::basic_string<CharT> &ltrim(std::basic_string<CharT> &s, const CharT *delims) {
    s.erase(0, s.find_first_not_of(delims));
    return s;
}

// trim from both ends of string (right then left)
template<class CharT> inline std::basic_string<CharT> &trim(std::basic_string<CharT> &s, const CharT *delims) { return ltrim(rtrim(s, delims), delims); }

namespace levenshtein {

// Levenshtein distance - Wagner–Fischer algorithm
struct Distance {
    Distance() = default;
    
    template<typename String> int operator() (const String &l, const String &r) {
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

};

} 

template<typename CharT, typename DistanceAlg> inline int distance(const CharT *l, const CharT *r) { 
    if(!l || !r)
        throw std::runtime_error("bad param");
    return DistanceAlg()(std::basic_string<CharT>(l), std::basic_string<CharT>(r)); 
}

template<typename CharT, typename DistanceAlg> inline int distance(const CharT *l, const std::basic_string<CharT> &r) { 
    if(!l)
        throw std::runtime_error("bad param");
    return DistanceAlg()(std::basic_string<CharT>(l), r); 
}

template<typename CharT, typename DistanceAlg> inline int distance(const std::basic_string<CharT> &l, const CharT *r) { 
    if(!r)
        throw std::runtime_error("bad param");
    return DistanceAlg()(l, std::basic_string<CharT>(r)); 
}

template<typename CharT, typename DistanceAlg> inline int distance(const std::basic_string<CharT> &l, const std::basic_string<CharT> &r) { 
    return DistanceAlg()(l, r); 
}