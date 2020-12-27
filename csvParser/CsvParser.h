#pragma once

#include <fstream>
#include <sstream>
#include <algorithm>

#include "TupleReader.h"

template<class ...Args>
class CsvParser {
public:
    class csvFacet : public std::ctype<char> {
        mask csvTable[table_size]{};
    public:
        explicit csvFacet(char delimiter, size_t refs = 0)
                : std::ctype<char>(&csvTable[0], false, refs) {
            std::copy_n(classic_table(), table_size, csvTable);
            csvTable[delimiter] = (mask) space;
            csvTable[' '] = lower;
        }
    };

    explicit CsvParser(std::ifstream &file, int skipLines = 0, char delimiter = ',')
    : file(file), skipLines(skipLines), delimiter(delimiter) {
        // skip lines
        for (int i = 0; i < skipLines; ++i) {
            std::string emptyString;
            std::getline(file, emptyString);
        }
        start = file.tellg();
    };

    class iterator {
    public:
        iterator(bool isEOF, std::ifstream &fileStream, char delimiter, int rowNumber, std::streampos pos)
        : isEOF(isEOF), fileStream(fileStream), delimiter(delimiter), rowNumber(rowNumber), currPosition(pos) {
            pTuple = new std::tuple<Args...>;
            if (isEOF) {
                return;
            }
            readTuple();
        }

        ~iterator() {
            delete pTuple;
        }

        void setDelimiter(std::istringstream &stringStream) {
            std::locale loc(std::locale::classic(), new csvFacet(delimiter));
            stringStream.imbue(loc);
        }

        void readTuple() {
            if (currPosition == EOF) {
                isEOF = true;
                return;
            }
            fileStream.clear();
            fileStream.seekg(currPosition);
            std::string currLine;
            std::getline(fileStream, currLine);
            currPosition = fileStream.tellg();

            std::istringstream stringStream(currLine);
            setDelimiter(stringStream);
            try {
                TupleReader<sizeof...(Args) - 1, Args...>::read(stringStream, *pTuple, rowNumber);
            } catch (CsvParserException &exception) {
                std::cerr << exception.what() << ", line " << exception.getRowToPrint() <<
                ", column " << exception.getColumnToPrint() << std::endl;
            }

            rowNumber++;
        }

        iterator &operator++() {
            readTuple();
            return *this;
        }

        iterator operator++(int) {
            iterator old = *this;
            (*this)++;
            return old;
        }

        bool operator==(const iterator &other) const {
            if (isEOF && other.isEOF) {
                return true;
            }
            return (*pTuple == *other.pTuple);
        }

        bool operator!=(const iterator &other) const {
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
        size_t rowNumber;
        std::streampos currPosition;
    };

    // methods for iterating
    iterator begin() {
        return iterator(false, file, delimiter, 1 + skipLines, start);
    }

    iterator end() {
        return iterator(true, file, delimiter, 0, EOF);
    }

private:
    int skipLines;
    std::ifstream &file;
    char delimiter;
    std::streampos start;
};



