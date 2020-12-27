#pragma once

#include <exception>
#include <string>
#include <utility>

class CsvParserException : public std::exception {
public:
    [[nodiscard]] const char *what() const noexcept override = 0;
    std::string getRowToPrint() {
        return std::to_string(rowNumber);
    }
    std::string getColumnToPrint() {
        return std::to_string(columnNumber);
    }
protected:
    size_t rowNumber = 0;
    size_t columnNumber = 0;
};

class NotEnoughArgs : public CsvParserException {
public:
    explicit NotEnoughArgs(size_t row, size_t column) {
        rowNumber = row;
        columnNumber = column;
    }
    [[nodiscard]] const char *what() const noexcept override {
        return "Not enough arguments";
    }
};

class WrongArg : public CsvParserException {
public:
    explicit WrongArg(size_t row, size_t column) {
        rowNumber = row;
        columnNumber = column;
    }
    [[nodiscard]] const char *what() const noexcept override {
        return "Wrong data";
    }
};
