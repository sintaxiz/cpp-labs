#pragma once

#include "LinkedListException.h"

#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <ostream>
#include <memory>


// Looped doubly connected List
template<class T>
class LinkedList {

private:
    struct node {
        node *next = nullptr;
        node *previous = nullptr;
        T data = T();

        node() = default;

        explicit node(T data, node *previous = nullptr, node *next = nullptr) :
                data(data), previous(previous), next(next) {}
    };

    node *tail;
    size_t size;

public:

    /* Constructors & destructors */

    // 1. Default constructor
    LinkedList() : size(0), tail(new node()) {
        tail->next = tail;
        tail->previous = tail;
    }

    // 2. Copy constructor
    // Allocate new memory and copy data from other
    LinkedList(const LinkedList &other) : LinkedList() {
        for (auto &item : other) {
            pushBack(item);
        }
    }

    // 3. Move constructor
    LinkedList(LinkedList &&other) noexcept {
        // take state
        size = other.size;
        tail = other.tail;

        // and make other object invalid
        other.size = 0;
        other.tail = nullptr;
    }

    // Destructor
    ~LinkedList() {
        if (!isEmpty()) {
            clear();
        }
        delete tail;
    }

    // 1. Copy assignment
    LinkedList &operator=(const LinkedList &other) {
        if (this == &other) {
            return *this;
        }
        if (!isEmpty()) {
            clear();
        }
        // Copy data
        for (auto item : other) {
            pushBack(item);
        }
        return *this;
    }

    // 2. Move assignment
    LinkedList &operator=(LinkedList &&other) noexcept {
        if (this == &other) {
            return *this;
        }
        // Firstly clear list if there any data
        if (!isEmpty()) {
            clear();
        }
        delete tail;
        // Then take data from "other"
        size = other.size;
        tail = other.head;
        // And make "other" empty
        other.size = 0;
        other.head = nullptr;

        return *this;
    }

    // Selectors
    int getSize() const {
        return size;
    }

    bool isEmpty() const {
        return size == 0;
    }

    // Bidirectional iterator
    class iterator {
        friend class LinkedList<T>; // for access to node pointer

        node *currPtr;
    public:

        // Default constructor
        iterator(node *current) : currPtr(current) {};

        // Copy constructor
        iterator(iterator const &other) {
            currPtr = other.currPtr;
        }

        // Copy assigment operator
        iterator &operator=(const iterator &other) {
            if ((*this) == other) {
                return *this;
            }
            currPtr = other.currPtr;
            return *this;
        }

        bool operator!=(const iterator &other) const {
            return currPtr != other.currPtr;
        }

        bool operator==(const iterator &other) const {
            return currPtr == other.currPtr;
        }

        // Return reference on current element of collection
        T &operator*() {
            return currPtr->data;
        }

        //Return pointer on current element of collection
        T *operator->() {
            return &(currPtr->data);
        }

        // ++, --: Return iterator that points on next/previous element
        // Prefix operator
        iterator &operator++() {
            currPtr = currPtr->next;
            return *this;
        }

        // Postfix operator
        iterator operator++(int) {
            iterator old = *this;
            ++(*this);
            return old;
        }

        iterator &operator--() {
            currPtr = currPtr->previous;
            return *this;
        }

        iterator operator--(int) {
            iterator old = *this;
            --(*this);
            return old;
        }

    };

    class constIterator {
        node *currPtr;
    public:
        explicit constIterator(node *current) : currPtr(current) {};

        constIterator(constIterator const &other) {
            currPtr = other.currPtr;
        }

        constIterator &operator=(const constIterator &other) {
            if (this == other) {
                return *this;
            }
            currPtr = other.currPtr;
            return *this;
        }

        bool operator!=(const constIterator &other) const {
            return currPtr != other.currPtr;
        }

        bool operator==(const constIterator &other) const {
            return currPtr == other.currPtr;
        }

        const T &operator*() {
            return currPtr->data;
        }

        const T *operator->() {
            return &(currPtr->data);
        }

        constIterator &operator++() {
            currPtr = currPtr->next;
            return *this;
        }

        constIterator operator++(int) {
            constIterator old = *this;
            ++(*this);
            return old;
        }

        constIterator &operator--() {
            currPtr = currPtr->previous;
            return *this;
        }

        constIterator operator--(int) {
            constIterator old = *this;
            --(*this);
            return old;
        }
    };

    iterator begin() {
        return iterator(tail->next);
    }

    iterator end() {
        return iterator(tail);
    }

    constIterator begin() const {
        return constIterator(tail->next);
    }

    constIterator end() const {
        return constIterator(tail);
    }

    constIterator cbegin() const {
        return constIterator(tail->next);
    }

    constIterator cend() const {
        return constIterator(tail);
    }

    /* Access to elements of collection */
    // Get a (const) reference to first element of collection
    T &front() {
        if (isEmpty()) {
            throw LinkedListException::EmptyException();
        } else {
            return *begin();
        }
    }

    const T &front() const {
        if (this->isEmpty()) {
            throw LinkedListException::EmptyException();
        } else {
            return *begin();
        }
    }

    // Get a (const) reference to last element of collection
    T &back() {
        if (this->isEmpty()) {
            throw LinkedListException::EmptyException();
        } else {
            return *(--end());
        }
    }

    const T &back() const {
        if (this->isEmpty()) {
            throw LinkedListException::EmptyException();
        } else {
            return *(--end());
        }
    }

    // Modifiers
    // Delete element on position from list
    iterator erase(iterator position) {
        if (isEmpty() || position == end()) {
            throw LinkedListException::EmptyException();
        };

        node *nextNode = position.currPtr->next;
        node *prevNode = position.currPtr->previous;
        prevNode->next = nextNode;
        nextNode->previous = prevNode;

        iterator next = iterator(nextNode);
        delete position.currPtr;
        size--;
        return next;
    }

    // Erase in some range (not including end)
    iterator erase(iterator begin, iterator end) {
        iterator it = begin;
        while (it != end) {
            it = erase(it);
        }
        return end;
    }

    // Delete all elements with data == value
    void remove(const T &value) {
        if (isEmpty()) {
            return;
        }
        auto it = begin();
        while (it != end()) {
            if ((*it) == value) {
                it = erase(it);
            }
            else {
                it++;
            }
        }
    }

    void clear() {
        if (!isEmpty()) {
            iterator current = begin();
            while (current != end()) {
                current = erase(current);
            }
        }
    }

    // Delete last element
    void popBack() {
        erase(--end());
    }

    // Delete first element (head)
    void popFront() {
        erase(begin());
    }

    // Insert last element
    void pushBack(const T &value) {
        insert(end(), value);
    }

    // Insert first element (head)
    void pushFront(const T &value) {
        insert(begin(), value);
    }

    // Insert some value before iterator "before". If list is empty, creates new head.
    iterator insert(iterator before, const T &value) {
        node *newNode = new node(value);
        newNode->previous = before.currPtr->previous;
        newNode->next = before.currPtr;
        before.currPtr->previous->next = newNode;
        before.currPtr->previous = newNode;
        size++;
        return iterator(newNode);
    }

    // Appends other to this
    LinkedList &operator+=(const LinkedList &other) {
        if (other.isEmpty()) {
            return *this;
        }
        for (auto item : other) {
            pushBack(item);
        }
        return *this;
    }

};

// Concatenate 2 lists and return result
template<class T>
LinkedList<T> operator+(const LinkedList<T> &left, const LinkedList<T> &right) {
    LinkedList<T> jointList;
    jointList += left;
    jointList += right;
    return jointList;
}

/* External operators of equality: check if 2 lists are equal */
template<class T>
bool operator!=(const LinkedList<T> &left, const LinkedList<T> &right) {
    return !(left == right);
}

template<class T>
bool operator==(const LinkedList<T> &left, const LinkedList<T> &right) {
    if (&left == &right) {
        return true;
    }
    if (left.getSize() != right.getSize()) {
        return false;
    }
    auto itLeft = left.begin();
    auto itRight = left.begin();
    while (itLeft != left.end()) {
        if (*itLeft != *itRight) {
            return false;
        }
        ++itLeft;
        ++itRight;
    }
    if (*(left.end()) != *(right.end())) {
        return false;
    }
    return true;
}


// For writing list to stream
template<class T>
std::ostream &operator<<(std::ostream &os, const LinkedList<T> &list) {
    for (auto &item : list) {
        os << item << " ";
    }
    return os;
}


