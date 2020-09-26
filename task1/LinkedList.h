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

    Node *head;
    Node *tail;
    size_t size;


public:

    /* КОНСТРУКТОРЫ И ДЕСТРУКТОР */

    // 1. Конструктор по умолчанию
    LinkedList() : size(0ull), head(nullptr), tail(nullptr) {}  // : Node() ... size() -- список инициализации

    // 2. Конструктор копирования
    // создается автоматически, просто копирует блок памяти в новую выделенную
    // LinkedList(const LinkedList &other) = delete;
    LinkedList(const LinkedList &other) {

        head = nullptr;
        tail = nullptr;
        size = 0;
        Node *otherNode = other.tail;
        for (size_t i = 0; i < other.size; ++i) {
            value_type data = otherNode->data;
            push_front(data);
            otherNode = otherNode->next;
        }

        /*head = other.head;
        tail = other.tail;
        Node *otherNode = other.tail;
        Node *newNode = new Node(otherNode);
        for (size_t i = 0; i < size; ++i) {
            otherNode = otherNode->next;
            newNode = new Node(otherNode);
        }
        //
        head = new Node(other.head);
        Node *tmp = other.head->next;
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
        return (size == 0 || head == nullptr || tail == nullptr);
    }

    // Модификаторы
    //Вставляет элемент в начало списка
    void push_front(const value_type &value) {
        if (head == nullptr) {
            if (tail != nullptr) {
                std::cout << "WTFFFF";
                exit(666);
            }
            Node *newNode = new Node(value);
            newNode->previous = newNode;
            newNode->next = newNode;
            head = newNode;
            tail = newNode;
            size++;
            return;
        }
        Node *newNode = new Node(value, head, tail); // создаём новую ноду, которая связывается с head и tail
        Node *oldBegin = head; // сохраняем прошлый front
        head = newNode;

        oldBegin->next = head; // прошлый front теперь ссылается на новую ноду
        tail->previous = head; // прошлый tail точно также

        size++;

    }


    //Добавляет значение value в конец списка.
    void push_back(const value_type &value) {
    }

    //Удаляет последний элемент списка.
    void pop_back() {
        Node *newEnd = tail->next;
        newEnd->previous = tail;
        head->next = newEnd;
        delete tail;
        tail = newEnd;
        size--;
    }

    //Удаляет первый элемент списка.
    void pop_front() {
        Node *newBegin = head->previous;
        newBegin->next = tail;
        tail->next = newBegin;
        delete head;
        head = newBegin;
    }


    // Операторы внутренние
    // Присоединяет other к списку.
    LinkedList &operator+=(const LinkedList &other) {
        if (other.isEmpty()) {
            return *this;
        }
        size += other.size;
        other.head->next = tail;
        other.tail->previous = head;
        head->next = other.head;
        tail->previous = other.head;
    }


    // Bidirectional iterator
    template<class ValueType>
    class iterator {
        Node *current;
    public:
        explicit iterator(Node *current) : current(current) {};

        iterator &operator=(const iterator &other) {
            if (this == other) {
                return *this;
            }
            current = other.current;
            return *this;
        }

        bool operator!=(const iterator &other) const {
            return current != other.current;
        }

        bool operator==(const iterator &other) const {
            return current == other.current;
        }

        //Возвращает ссылку на текущий элемент коллекции.
        value_type &operator*() {
            return current->data;
        }

        //Возвращает указатель на текущий элемент коллекции.
        value_type *operator->() {
            return &(current->data);
        }

        // префиксный оператор
        iterator &operator++() {
            current = current->next;
            return *this;
        }

        // постфиксный оператор
        iterator operator++(int) {
            iterator old = *this;
            ++old;
            return old;
        }

        iterator &operator--() {
            current = current->previous;
            return *this;
        }

        iterator operator--(int) {
            iterator old = *this;
            --this;
            return old;
        }

    };

    class const_iterator {

    };

    iterator<class ValueType> begin() {
        return iterator<ValueType>(head);
    }

    iterator<class ValueType> end() {
        return iterator<ValueType>(head);
    }


    /* Доступ к элементам */
    //Возвращает ссылку на первый элемент списка.
    value_type & front() {
        if(this->isEmpty()) {
            return 0;
        } else {
            return head->data;
        }
    }
    const value_type & front() const {
        if(this->isEmpty()) {
            return 0;
        } else {
            return head->data;
        }
    }
    //Возвращает ссылку на последний элемент списка.
    value_type & back();
    const value_type & back() const;


};
