#pragma once

#include <exception>
#include <string>
#include <utility>

class CalculatorException : public std::exception {
public:
    const char *what() const noexcept override = 0;
};


class OperationException : public CalculatorException {
    const char *what() const noexcept override {
        return "Unknown operation exception";
    }
};

class WrongVarException : public CalculatorException {
    const char *what() const noexcept override {
        return "There is no such variable";
    }
};

class NotEnoughArgsException : public OperationException {
    const char *what() const noexcept override {
        return "Not enough arguments for command";
    }
};

class DivisionByZeroException : public OperationException {
    const char *what() const noexcept override {
        return "Division by zero";
    }
};

