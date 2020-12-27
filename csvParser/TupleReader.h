#pragma once

#include <fstream>
#include <tuple>
#include "CsvParserException.h"

template<size_t N, class ...Args>
class TupleReader {
public:
    static void read(std::istream& is, std::tuple<Args...>& t, int rowNumber)
    {
        TupleReader<(N > 0 ? N - 1 : 0), Args...>::read(is, t, rowNumber);
            if (is.eof()) {
            throw NotEnoughArgs(rowNumber, N + 1);
        }
        is >> std::get<N>(t);
        if (is.fail()){
            throw WrongArg(rowNumber, N + 1);
        }
    }
};

// Частичная специализация
template<class ...Args>
class TupleReader<0, Args...> {
public:
    static void read(std::istream& is, std::tuple<Args...>& t, int rowNumber) {
        if (is.eof()) {
            throw NotEnoughArgs(rowNumber, 1);
        }
        is >> std::get<0>(t);
        if (is.fail()){
            throw WrongArg(rowNumber, 1);
        }
    }
};
