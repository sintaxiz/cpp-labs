#pragma once

#include <fstream>
#include <tuple>
#include "CsvParserException.h"

template<size_t N, class ...Args>
class TupleReader {
public:
    static void read(std::istream& i, std::tuple<Args...>& t, int rowNumber)
    {
        TupleReader<(N > 0 ? N - 1 : 0), Args...>::read(i, t, rowNumber);
        if (i.eof()) {
            throw NotEnoughArgs(rowNumber);
        }
        i >> std::get<N>(t);
    }
};

// Частичная специализация
template<class ...Args>
class TupleReader<0, Args...> {
public:
    static void read(std::istream& is, std::tuple<Args...>& t, int rowNumber) {
        if (is.eof()) {
            throw NotEnoughArgs(rowNumber);
        }
        is >> std::get<0>(t);
    }
};
