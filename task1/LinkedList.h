#pragma once

#include <cstddef>
#include <cstdlib>
#include <iostream>

template<class value_type>
class LinkedList {
private:
    struct Node {
        Node *next = nullptr;
        Node *previous = nullptr;
        value_type data = 0;

        Node() = default;

        explicit Node(value_type data, Node *previous = nullptr, Node *next = nullptr) :
                data(data), previous(previous), next(next) {}

        //копируется только дата!!!
        /* Node(const Node &node) :
                 next(nullptr),
                 previous(nullptr),
                 data(node.data) {}

         Node &operator=(const Node &other) {
             if (*this != other) {
                 next(nullptr);
                 previous(nullptr);
                 data(other.data);
             }
             return *this;
         }*/
    };

    Node *begin;
    Node *end;
    size_t size;


public:

    /* КОНСТРУКТОРЫ И ДЕСТРУКТОР */

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
        size = 0;
        for (int i = 0; i < other.size; ++i) {
            push_front();
        }
        // .... забираем состояние объекта

        other.size = 0; //
    }

    // Destructor (only one)
    ~LinkedList() {
        if (isEmpty()) {
            std::cout << "isEmpty list" << std::endl;
            return;
        }
        for (int i = 0; i < size; ++i) {
            pop_back();
        }
    }


    // Селекторы -- помечаем метод const

    /* Размерность */
    //Возвращает размер списка.
    int getSize() const {
        return size;
    }

    //Возвращает истину, если список пуст.
    bool isEmpty() const {
        return (size == 0 || begin == nullptr || end == nullptr);
    }

    // Модификаторы
    //Вставляет элемент в начало списка
    void push_front(const value_type &value) {
        if (begin == nullptr) {
            if (end != nullptr) {
                std::cout << "WTFFFF";
                exit(666);
            }
            Node *newNode = new Node(value);
            newNode->previous = newNode;
            newNode->next = newNode;
            begin = newNode;
            end = newNode;
            size++;
            return;
        }
        Node *newNode = new Node(value, begin, end); // создаём новую ноду, которая связывается с begin и end
        Node *oldBegin = begin; // сохраняем прошлый front
        begin = newNode;

        oldBegin->next = begin; // прошлый front теперь ссылается на новую ноду
        end->previous = begin; // прошлый end точно также

        size++;

    }


    //Добавляет значение value в конец списка.
    void push_back(const value_type & value) {
    }

    //Удаляет последний элемент списка.
    void pop_back() {
        Node *newEnd = end->next;
        newEnd->previous = end;
        begin->next = newEnd;
        delete end;
        end = newEnd;
        size--;
    }

    //Удаляет первый элемент списка.
    void pop_front() {
        Node *newBegin = begin->previous;
        newBegin->next = end;
        end->next = newBegin;
        delete begin;
        begin = newBegin;
    }



    // Операторы внутренние
    // Присоединяет other к списку.
    LinkedList &operator +=(const LinkedList &other) {
        if (other.isEmpty()) {
            return *this;
        }
        size += other.size;
        other.begin->next = end;
        other.end->previous = begin;
        begin->next = other.begin;
        end->previous = other.begin;
    }

};