#pragma once

#include <exception>
#include <string>
#include <utility>

class CsvParserException : public std::exception {
public:
    const char *what() const noexcept override = 0;
    std::string getRow() {
        return std::to_string(rowNumber);
    }
protected:
    size_t rowNumber;
};

class NotEnoughArgs : public CsvParserException {
public:
    explicit NotEnoughArgs(size_t row) {
        rowNumber = row;
    }
    const char *what() const noexcept override {
        return "Not enough arguments";
    }
};
