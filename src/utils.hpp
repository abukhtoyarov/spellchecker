#pragma once
#include <string>
#include <algorithm>

namespace details {

template<class CharT> inline int tolower(int c);
template<> inline int tolower<char>(int c) { return std::tolower(c); }
template<> inline int tolower<wchar_t>(int c) { return std::towlower(c); }

}

// преобразование строки к нижнему регистру
template<class CharT> inline std::basic_string<CharT> to_lower(const std::basic_string<CharT> &str) {
    auto ret = str;
    std::transform(str.begin(), str.end(), ret.begin(), [] (CharT c) { return details::tolower<CharT>(c); });
    return ret;
}

// отсечение символов delims справа
template<class CharT> inline std::basic_string<CharT> &rtrim(std::basic_string<CharT> &s, const CharT *delims) {
    s.erase(s.find_last_not_of(delims) + 1);
    return s;
}

// отсечение символов delims слева
template<class CharT> inline std::basic_string<CharT> &ltrim(std::basic_string<CharT> &s, const CharT *delims) {
    s.erase(0, s.find_first_not_of(delims));
    return s;
}

// отсечение символов delims справа и слева
template<class CharT> inline std::basic_string<CharT> &trim(std::basic_string<CharT> &s, const CharT *delims) { return ltrim(rtrim(s, delims), delims); }
