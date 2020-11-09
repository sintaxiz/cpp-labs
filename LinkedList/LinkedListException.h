#pragma once

#include <exception>

class LinkedListException {
public:
    class EmptyException : public std::exception {
        const char *what() const throw(){
            return "List is empty!";
        }
    };
};
