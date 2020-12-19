#pragma once

#include <fstream>
#include <sstream>
#include <algorithm>

#include "TupleReader.h"

template<class ...Args>
class CsvParser {
public:
    class my_ctype : public std::ctype<char> {
        mask my_table[table_size];
    public:
        my_ctype(char delimiter, size_t refs = 0)
                : std::ctype<char>(&my_table[0], false, refs) {
            std::copy_n(classic_table(), table_size, my_table);
            my_table[delimiter] = (mask) space;
            my_table[' '] = lower;
        }
    };

    CsvParser(std::ifstream &file, int skipLines, char delimiter = ',')
    : file(file), skipLines(skipLines), delimiter(delimiter) {
        // skip lines
        for (int i = 0; i < skipLines; ++i) {
            std::string emptyString;
            std::getline(file, emptyString);
        }
    };

    class iterator {
    public:
        iterator(bool isEOF, std::ifstream &fileStream, char delimiter)
        : isEOF(isEOF), fileStream(fileStream), delimiter(delimiter) {
            pTuple = new std::tuple<Args...>;
            if (isEOF) {
                return;
            }
            readTuple();
        }

        ~iterator() {
            delete pTuple;
        }

        void setDelimeter(std::istringstream &stringStream) {
            std::locale loc(std::locale::classic(), new my_ctype(delimiter));
            stringStream.imbue(loc);
        }

        void readTuple() {
            if (fileStream.eof()) {
                isEOF = true;
                fileStream.clear();
                fileStream.seekg(0);
                return;
            }
            std::string currLine;
            std::getline(fileStream, currLine);
            std::istringstream stringStream(currLine);
            setDelimeter(stringStream);
            stringStream >> *pTuple;

        }

        iterator &operator++() {
            readTuple();
            return *this;
        }

        iterator operator++(int) {
            iterator old = *this;
            readTuple();
            return old;
        }

        bool operator==(const iterator &other) const {
            return (*pTuple == *other.pTuple);
        }

        bool operator!=(const iterator &other) const {
            if (isEOF) {
                return false;
            }
            return !(*this == other);
        }

        std::tuple<Args...> &operator*() const {
            return *pTuple;
        }

    private:
        std::tuple<Args...> *pTuple;
        std::ifstream &fileStream;
        bool isEOF;
        char delimiter;
    };

    // methods for iterating
    iterator begin() {
        return iterator(false, file, delimiter);
    }

    iterator end() {
        return iterator(true, file, delimiter);
    }

private:
    int skipLines;
    std::ifstream &file;
    char delimiter;

};



