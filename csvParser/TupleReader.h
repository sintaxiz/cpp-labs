#pragma once

#include <fstream>
#include <tuple>

template<size_t N, class ...Args>
class TupleReader {
public:
    static void read(std::istream& i, std::tuple<Args...>& t)
    {
        TupleReader<(N > 0 ? N - 1 : 0), Args...>::read(i, t);
        i >> std::get<N>(t);
    }
};

// Частичная специализация
template<class ...Args>
class TupleReader<0, Args...> {
public:
    static void read(std::istream& is, std::tuple<Args...>& t) {
        is >> std::get<0>(t);
    }
};


template<class ...Args>
std::istream
&operator >>(std::istream& is, std::tuple<Args...>& t) {
    TupleReader<sizeof...(Args) - 1, Args...>::read(is, t);
    return is;
}




