#pragma once

#include <exception>

class LinkedListException {
    class FileException : public std::exception{
        const char *what() const throw() {
            return "Can not open file";
        }
    };
};
