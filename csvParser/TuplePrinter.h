#pragma once

#include <iostream>
#include <tuple>

template<class Tuple, size_t N, class CharT, class Traits = std::char_traits<CharT>>
class TuplePrinter {
public:
    static void print(std::basic_ostream<CharT, Traits>& os, const Tuple &tpl) {
        TuplePrinter<Tuple, N - 1, CharT, Traits>::print(os, tpl);
        os << ", " << std::get<N - 1>(tpl);
    }
};

// Частичная специализация
template<class Tuple, class CharT, class Traits>
class TuplePrinter<Tuple, 1, CharT, Traits> {
public:
    static void print(std::basic_ostream<CharT, Traits>& os, const Tuple &tpl) {
        os << std::get<0>(tpl);
    }
};

template<class ...Args, class CharT, class Traits = std::char_traits<CharT>>
std::basic_ostream<CharT, Traits>
&operator <<(std::basic_ostream<CharT, Traits>& os, std::tuple<Args...> const& t) {
    TuplePrinter<decltype(t),sizeof...(Args),CharT, Traits>::print(os, t);
    return os;
}



