#include <iostream>
#include <algorithm>
#include "LinkedList.h"
int main(int argc, char **argv) {
    LinkedList<int> list1;
    for (int i = 1; i <= 100; ++i) {
        list1.push_front(i);
    }

    auto itt = std::find_if(list1.begin(), list1.end(), [](int i){ return ((i%2) == 1);});
    std::cout << "The first odd value is " << *itt << '\n';
    LinkedList<int> list2;
    for (int i = 1; i <= 100; ++i) {
        list2.push_front(i);
    }

    std::cout << list1 << std::endl;
    std::cout << list1.getSize() << std::endl;
    std::cout << list2 << std::endl;
    std::cout << list2.getSize() << std::endl;

    return 0;
}
