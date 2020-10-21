#pragma once

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
    node *tail;
    size_t size;

public:

    /* КОНСТРУКТОРЫ И ДЕСТРУКТОР */

    // 1. Конструктор по умолчанию
    LinkedList() : size(0ull), head(nullptr), tail(nullptr) {}  // : node() ... size() -- список инициализации

    // 2. Конструктор копирования
    // создается автоматически, просто копирует блок памяти в новую выделенную
    // LinkedList(const LinkedList &other) = delete;
    LinkedList(const LinkedList &other) {
        head = nullptr;
        tail = nullptr;
        size = 0;
        node *other_node = other.tail;
        for (size_t i = 0; i < other.size; ++i) {
            value_type data = other_node->data;
            push_front(data);
            other_node = other_node->next;
        }
    }

    // 3. Move-конструктор, переносит состояние other в новый объект
    LinkedList(LinkedList &&other) noexcept {
        size = other.size;
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

    // Оператор присваивания копированием (cope assignment)
    LinkedList & operator=(const LinkedList & other) {
        if (this == &other) {
            return *this;
        }

        for (int j = 0; j < size; ++j) {
            pop_front();
        }

        for (value_type &item : other) {
            push_back(item);
        }

        return *this;
    }

    // Оператор присваивания перемещением (move assignment)
    LinkedList & operator=(LinkedList && other) noexcept {
        if(this == &other){
            return *this;
        }

        for (int i = 0; i < size; ++i) {
            pop_front();
        }

        size = other.size;
        head = other.head;
        tail = other.tail;

        other.size = 0;
        other.head = nullptr;
        other.tail = nullptr;

        return *this;
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
            node *newNode = new node(value);
            newNode->previous = newNode;
            newNode->next = newNode;
            head = newNode;
            tail = newNode;
            size++;
            return;
        }
        node *newNode = new node(value, head, tail); // создаём новую ноду, которая связывается с head и tail
        head->next = newNode;
        head = newNode;

        tail->previous = head; // прошлый tail точно также

        size++;

    }


    //Добавляет значение value в конец списка.
    void push_back(const value_type &value) {

        if (head == nullptr) {
            if (tail != nullptr) {
                std::cout << "WTFFFF";
                exit(666);
            }
            node *newNode = new node(value);
            newNode->previous = newNode;
            newNode->next = newNode;
            head = newNode;
            tail = newNode;
            size++;
            return;
        }
        node *new_back = new node(value, head, tail); // создаём новую ноду, которая связывается с head и tail
        node *old_back = tail; // сохраняем прошлый back
        tail = new_back;

        old_back->previous = tail; // прошлый front теперь ссылается на новую ноду
        head->next = tail; // прошлый tail точно также

        size++;
    }

    //Удаляет последний элемент списка.
    void pop_back() {
        node *newEnd = tail->next;
        newEnd->previous = tail;
        head->next = newEnd;
        delete tail;
        tail = newEnd;
        size--;
    }

    //Удаляет первый элемент списка.
    void pop_front() {
        node *newBegin = head->previous;
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
        return *this;
    }


    // Bidirectional iterator
    class iterator {
        node *curr_ptr;
    public:
        explicit iterator(node *current) : curr_ptr(current) {};

        iterator &operator=(const iterator &other) {
            if (this == other) {
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

        //Возвращает ссылку на текущий элемент коллекции.
        value_type &operator*() {
            return curr_ptr->data;
        }

        //Возвращает указатель на текущий элемент коллекции.
        value_type *operator->() {
            return &(curr_ptr->data);
        }

        // префиксный оператор
        iterator &operator++() {
            curr_ptr = curr_ptr->previous;
            return *this;
        }

        // постфиксный оператор
        iterator operator++(int) {
            iterator old = *this;
            ++(*this);
            return old;
        }

        iterator &operator--() {
            curr_ptr = curr_ptr->next;
            return *this;
        }

        iterator operator--(int) {
            iterator old = *this;
            --this;
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

        //Возвращает ссылку на текущий элемент коллекции.
        const value_type &operator*() {
            return curr_ptr->data;
        }

        //Возвращает указатель на текущий элемент коллекции.
        const value_type *operator->() {
            return &(curr_ptr->data);
        }

        // префиксный оператор
        const_iterator &operator++() {
            curr_ptr = curr_ptr->previous;
            return *this;
        }

        // постфиксный оператор
        const_iterator operator++(int) {
            iterator old = *this;
            ++(*this);
            return old;
        }

        const_iterator &operator--() {
            curr_ptr = curr_ptr->next;
            return *this;
        }

        const_iterator operator--(int) {
            iterator old = *this;
            --this;
            return old;
        }

    };

    iterator begin() {
        return iterator(head);
    }

    iterator end() {
        return iterator(tail);
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
    value_type & back(){
        if (this->isEmpty()) {
            return 0;
        } else {
            return tail->data;
        }
    }
    const value_type & back() const {
        if (this->isEmpty()) {
            return 0;
        } else {
            return tail->data;
        }
    }


    friend std::ostream& operator<<(std::ostream& os, LinkedList& list) {
        for (LinkedList<int>::iterator it = list.begin(); it != list.end(); it++) {
             os << *it << " ";
        }
        return os;
    }
};
