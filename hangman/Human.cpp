#include <iostream>
#include "Human.h"

char Human::makeTurn() {
    std::cout << "Enter a letter:\n";
    char letter = 0;
    std::cin >> letter;
    return letter;
}
