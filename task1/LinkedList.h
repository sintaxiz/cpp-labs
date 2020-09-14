#pragma once

#include <cstddef>
#include <cstdlib>
#include <iostream>

/*#include <bits/valarray_before.h>
#include <cstddef>*/

template<class value_type>
class LinkedList {
private:
    struct Node {
        Node *next = nullptr;
        Node *previous = nullptr;
        value_type data = 0;

        Node() = default;
        Node(value_type data, Node *next = nullptr, Node *prev = nullptr) :
            next(next),
            previous(prev),
            data(data) {}
            //копируется только дата!!!
        Node(const Node &node) :
            next(nullptr),
            previous(nullptr),
            data(node.data) {}
        Node& operator=(const Node& other) {
            if (*this != other) {
                next(nullptr);
                previous(nullptr);
                data(other.data);
            }
            return *this;
        }
    };

    Node *begin;
    Node *end;
    size_t size;
public:

    //Вставляет элемент в начало списка
    void push_front(const value_type & value) {
        if (begin == nullptr) {
            if(end != nullptr) {
                std::cout << "WTFFFF";
                exit(666);
            }
        }
        Node *newNode = new Node(value); // создаём новую ноду
        Node *oldBegin = begin; // сохраняем прошлый front
        begin = newNode;

        oldBegin->next = begin; // прошлый front теперь ссылается на новую ноду
        end->previous = begin; // прошлый end точно также

        size++;

    }

    // Конструкторы, деструкторы

    // 1. Конструктор по умолчанию
    LinkedList() : size(0ull), begin(nullptr), end(nullptr) {}  // : Node() ... size() -- список инициализации

    // 2. Конструктор копирования
    // создается автоматически, просто копирует блок памяти в новую выделенную
    // LinkedList(const LinkedList &other) = delete;
    LinkedList(const LinkedList &other) {

        begin = nullptr;
        end = nullptr;
        size = 0;
        Node *otherNode = other.end;
        for (size_t i = 0; i < other.size; ++i) {
            value_type data = otherNode->data;
            push_front(data);
            otherNode = otherNode->next;
        }

        /*begin = other.begin;
        end = other.end;
        Node *otherNode = other.end;
        Node *newNode = new Node(otherNode);
        for (size_t i = 0; i < size; ++i) {
            otherNode = otherNode->next;
            newNode = new Node(otherNode);
        }
        //
        begin = new Node(other.begin);
        Node *tmp = other.begin->next;
        for (size_t i = 1ull; i < size; ++i) {
            Node * newNode = new Node(tmp);

        }*/
    }

    // 3. Move-конструктор, переносит состояние other в новый объект
    LinkedList(LinkedList &&other) noexcept {
        size = other.size;
        // .... забираем состояние объекта

        other.size = 0; //
    }

    // Destructor (only one)
    ~LinkedList() {
        Node *currentNode = begin;
        for (int i = 0; i < size; ++i) {
            Node *nodeToDelete = currentNode;
            currentNode = currentNode->next;
            delete nodeToDelete;
        }
    }

    int getSize() {
        return size;
    }

    // Селекторы -- помечаем метод const, модификаторы
};