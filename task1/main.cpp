#include <iostream>
#include "LinkedList.h"

// Зацикленный LinkedList
int main() {
    std::cout << "Hello, World!" << std::endl;

    LinkedList<int> myList;
    std::cout << myList.getSize() << std::endl;
    myList.push_front(10);
    std::cout << myList.getSize() << std::endl;
    myList.push_back(100);

    std::cout << myList.getSize() << std::endl;

    std::cout << myList.getSize() << std::endl;
    myList.push_front(1000);
    std::cout << myList.getSize() << std::endl;

    LinkedList<int> anotherList;
    anotherList.push_front(1000);
    anotherList.push_front(1000);


    std::cout << myList.getSize() << std::endl;
    myList += anotherList;
    std::cout << myList.getSize();

    return 0;
}
