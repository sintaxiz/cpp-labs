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
        T data = 0;

        node() = default;

        explicit node(T data, node *previous = nullptr, node *next = nullptr) :
                data(data), previous(previous), next(next) {}
    };
    node *head;
    size_t size;

public:

    /* Constructors & destructors */

    // 1. Default constructor
    LinkedList() : size(0ull), head(nullptr) {} // just an empty list

    // 2. Copy constructor
    // Allocate new memory and copy data from other
    LinkedList(const LinkedList &other) {
        head = nullptr;
        size = 0;
        auto it = other.end();
        for (size_t i = 0; i < other.getSize(); --it, i++) {
            pushFront(*it);
        }
    }

    // 3. Move constructor
    LinkedList(LinkedList &&other) noexcept {
        // take state
        size = other.size;
        head = other.head;

        // and make other object invalid
        other.size = 0;
        other.head = nullptr;
    }

    // Destructor
    ~LinkedList() {
        if (!isEmpty()) {
            clear();
        }
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
        constIterator it = other.end();
        for (size_t i = 0; i < other.size; --it, i++) {
            pushFront(*it);
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
        // Then take data from "other"
        size = other.size;
        head = other.head;
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
        return (size == 0 || head == nullptr);
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
        return iterator(head);
    }
    iterator end() {
        return isEmpty() ? iterator(nullptr) : iterator(head->previous);
    }

    constIterator begin() const {
        return constIterator(head);
    }
    constIterator end() const {
        return isEmpty() ? constIterator(nullptr) : constIterator(head->previous);
    }

    constIterator cbegin() const {
        return constIterator(head);
    }

    constIterator cend() const {
        return constIterator(head->previous);
    }

    /* Access to elements of collection */
    // Get a (const) reference to first element of collection
    T &front() {
        if (isEmpty()) {
            throw LinkedListException::EmptyException();
        } else {
            return head->data;
        }
    }

    const T &front() const {
        if (this->isEmpty()) {
            throw LinkedListException::EmptyException();
        } else {
            return head->data;
        }
    }

    // Get a (const) reference to last element of collection
    T &back() {
        if (this->isEmpty()) {
            throw LinkedListException::EmptyException();
        } else {
            return head->previous->data;
        }
    }

    const T &back() const {
        if (this->isEmpty()) {
            throw LinkedListException::EmptyException();
        } else {
            return head->previous->data;
        }
    }

    // Modifiers
    // Delete element on position from list
    iterator erase(iterator position) {
        if (isEmpty()) {
            throw LinkedListException::EmptyException();
        };

        node *nextNode = position.currPtr->next;
        node *prevNode = position.currPtr->previous;
        prevNode->next = nextNode;
        nextNode->previous = prevNode;

        iterator next = iterator(nextNode);

        if (position.currPtr == head) {
            head = nextNode;
        }
        delete position.currPtr;
        size--;
        return next;
    }

    // Erase in some range (including end)
    iterator erase(iterator begin, iterator end) {
        if (isEmpty()) {
            throw LinkedListException::EmptyException();
        };
        iterator it = begin;
        while(it != end) {
            it = erase(it);
        }
        return erase(it); // delete last element
    }

    // Delete all elements with data == value
    void remove(const T &value) {
        if (isEmpty()) {
            return;
        }
        for (auto it = begin(); it != end(); it++) {
            if ((*it) == value) {
                it = erase(it);
            }
        }
    }

    void clear() {
        if (isEmpty()) {
            throw LinkedListException::EmptyException();
        }
        iterator current = begin();
        while (current != end()) {
            current = erase(current);
        }
        delete head; // delete last node
        size = 0;
    }


    // Delete last element
    void popBack() {
        head->previous = erase(end()).currPtr;
    }

    // Delete first element (head)
    void popFront() {
        head = erase(begin()).currPtr;
    }

    // Insert last element
    void pushBack(const T &value) {
        insert(++end(), value);
    }

    // Insert first element (head)
    void pushFront(const T &value) {
        head = insert(begin(), value).currPtr;
    }

    // Insert some value before iteratore "before". If list is empty, creates new head.
    iterator insert(iterator before, const T &value) {
        node *newNode = new node(value);
        if (isEmpty()) {
            newNode->previous = newNode;
            newNode->next = newNode;
            head = newNode;
        } else {
            newNode->previous = before.currPtr->previous;
            newNode->next = before.currPtr;
            before.currPtr->previous->next = newNode;
            before.currPtr->previous = newNode;
        }
        size++;
        return iterator(newNode);
    }

    // Appends other to this
    LinkedList &operator+=(const LinkedList &other) {
        if (other.isEmpty()) {
            return *this;
        }
        constIterator it = other.cbegin();
        for (int i = 0; i < other.getSize(); ++i, ++it) {
            pushBack(*it);
        }
        return *this;
    }

    /* External operators of equality: check if 2 lists are equal */
    friend bool operator!=(const LinkedList & left, const LinkedList & right) {
        return !(left == right);
    }
    friend bool operator==(const LinkedList & left, const LinkedList & right) {
        if (left.isEmpty()) {
            return right.isEmpty();
        }
        if (left.size != right.size) {
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
    friend std::ostream &operator<<(std::ostream &os, const LinkedList &list) {
        for (auto &item : list) {
            os << item << " ";
        }
        return os;
    }

    // Concatenate 2 lists and return result
    friend LinkedList operator+(const LinkedList & left, const LinkedList & right) {
        LinkedList jointList;
        jointList += left;
        jointList += right;
        return jointList;
    }
};



