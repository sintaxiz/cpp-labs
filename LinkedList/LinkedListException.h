#pragma once

#include <exception>

namespace LinkedListException {
    class EmptyException : public std::exception {
        const char *what() const throw(){
            return "List is empty!";
        }
    };
};
