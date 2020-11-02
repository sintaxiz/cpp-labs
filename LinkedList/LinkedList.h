#pragma once

#include "LinkedListException.h"

#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <ostream>
#include <memory>


// Зацикленный двухсвязный список
template<class value_type>
class LinkedList {

private:
    struct node {
        node *next = nullptr;
        node *previous = nullptr;
        value_type data = 0;

        node() = default;
        explicit node(value_type data, node *previous = nullptr, node *next = nullptr) :
                data(data), previous(previous), next(next) {}
    };
    node *head;
    size_t size;

public:

    /* Constructors & destructors */

    // 1. Default constructor
    LinkedList() : size(0ull), head(nullptr) {}

    //TODO:
    // 2. Copy constructor
    // создается автоматически, просто копирует блок памяти в новую выделенную
    LinkedList(const LinkedList &other) {
        head = nullptr;
        size = 0;
        for (auto it = other.cbegin(); it != other.cend(); it++) {
            push_back(*it);
        }
        push_back(*(other.cend()));
    }

    // 3. Move constructor
    LinkedList(LinkedList &&other) noexcept {
        size = other.size;
        head = other.head;

        other.size = 0;
        other.head = nullptr;
    }

    // Destructor (only one)
    ~LinkedList() {
        if (!isEmpty()) {
            clear();
        }
    }

    // Copy assignment
    LinkedList & operator=(const LinkedList & other) {
        if (this == &other) {
            return *this;
        }
        // Clear our list (if size > 1)
        ~(*this); // TODO: can i do it that way?
        for (int j = 0; j < size; ++j) {
            pop_front();
        }
        // Copy data
        for (value_type &item : other) {
            push_back(item);
        }
        return *this;
    }

    // Move assignment
    LinkedList & operator=(LinkedList && other) noexcept {
        if(this == &other){
            return *this;
        }
        // Firstly clear list if there any data
        for (int i = 0; i < size; ++i) {
            pop_front();
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
        friend class LinkedList<value_type>; // for access to node pointer

        node *curr_ptr;
    public:
        explicit iterator(node *current) : curr_ptr(current) {};

        iterator &operator=(const iterator &other) {
            if (this != other) {
                return *this;
            }
            curr_ptr = other.curr_ptr;
            return *this;
        }

        bool operator!=(const iterator &other) const {
            return curr_ptr != other.curr_ptr;
        }
        bool operator==(const iterator &other) const {
            return curr_ptr == other.curr_ptr;
        }

        // Return reference on current element of collection
        value_type &operator*() {
            return curr_ptr->data;
        }
        //Return pointer on current element of collection
        value_type *operator->() {
            return &(curr_ptr->data);
        }

        // ++, --: Return iterator that points on next/previous element
        // Prefix operator
        iterator &operator++() {
            curr_ptr = curr_ptr->next;
            return *this;
        }
        // Postfix operator
        iterator operator++(int) {
            iterator old = *this;
            ++(*this);
            return old;
        }
        iterator &operator--() {
            curr_ptr = curr_ptr->previous;
            return *this;
        }
        iterator operator--(int) {
            iterator old = *this;
            --(*this);
            return old;
        }

    };

    class const_iterator {
        node *curr_ptr;
    public:
        explicit const_iterator(node *current) : curr_ptr(current) {};

        const_iterator &operator=(const const_iterator &other) {
            if (this == other) {
                return *this;
            }
            curr_ptr = other.curr_ptr;
            return *this;
        }

        bool operator!=(const const_iterator &other) const {
            return curr_ptr != other.curr_ptr;
        }
        bool operator==(const const_iterator &other) const {
            return curr_ptr == other.curr_ptr;
        }

        const value_type &operator*() {
            return curr_ptr->data;
        }
        const value_type *operator->() {
            return &(curr_ptr->data);
        }

        const_iterator &operator++() {
            curr_ptr = curr_ptr->next;
            return *this;
        }
        const_iterator operator++(int) {
            const_iterator old = *this;
            ++(*this);
            return old;
        }
        const_iterator &operator--() {
            curr_ptr = curr_ptr->previous;
            return *this;
        }
        const_iterator operator--(int) {
            const_iterator old = *this;
            --this;
            return old;
        }
    };

    iterator begin() {
        return iterator(head);
    }
    const_iterator begin() const {
        return const_iterator(head);
    }

    iterator end() {
        return iterator(head->previous);
    }
    const_iterator end() const {
        return const_iterator(head->previous);
    }

    const_iterator cbegin() const {
        return const_iterator(head->previous);
    }
    const_iterator cend() const {
        return const_iterator(head->next);
    }

    /* Access to elements of collection */
    // Get a (const) reference to first element of collection
    value_type & front() {
        if(isEmpty()) {
            return 0; // TODO: make exception
        } else {
            return head->data;
        }
    }
    const value_type & front() const {
        if(this->isEmpty()) {
            return 0; // TODO: make exception
        } else {
            return head->data;
        }
    }
    // Get a (const) reference to last element of collection
    value_type & back(){
        if (this->isEmpty()) {
            return 0; // TODO: make exception
        } else {
            return head->next->data;
        }
    }
    const value_type & back() const {
        if (this->isEmpty()) {
            return 0; // TODO: make exception
        } else {
            return head->next->data;
        }
    }

    // Modifiers
    iterator erase(iterator position) {
        if (isEmpty()){}; // TODO: exception?
        position.curr_ptr->next = position.curr_ptr->previous;
        position.curr_ptr->previous = position.curr_ptr->next;
        iterator next = iterator(position.curr_ptr->next);
        delete position.curr_ptr;
        return next;
    }

    iterator erase(iterator begin, iterator end) {
        if (isEmpty()){}; // TODO: exception?
        while (begin != end) {
            begin = erase(begin); // TODO: check work
        }
        return end;
    }

    void remove(const value_type &value) {
        if (isEmpty()){
            return;
        }
        for (auto it = begin();it != end(); it++) {
            if((*it) == value) {
                it = erase(it);
            }
        }
    }

    void clear() {
        erase(begin(), end());
    }

    void pop_back() {
        head->previous = erase(end()).curr_ptr;
    }
    void pop_front() {
        head = erase(front()).curr_ptr;
    }

    iterator insert(iterator before, const value_type & value) {
        node *newNode = new node(value, before.curr_ptr->previous, before.curr_ptr)
        before.curr_ptr->previous = newNode;
        before.curr_ptr->previous->next = newNode;
        size++;
        return iterator(newNode);
    }

    void push_back(const value_type & value) {
        insert(end(), value);
    }
    void push_front(const value_type & value) {
        insert(begin(), value);
    }

    // Операторы внутренние
    // Присоединяет other к списку.
    LinkedList &operator+=(const LinkedList &other) {
        if (other.isEmpty()) {
            return *this;
        }
        size += other.size;
        other.head->next = head->next;
        other.head->next->previous = head;
        head->next = other.head;
        head->next->previous = other.head;
        return *this;
    }

    // For writing list
    friend std::ostream& operator<<(std::ostream& os, const LinkedList& list) {
        for (auto &item : list) {
            os << item << " ";
        }
        return os;
    }
};
