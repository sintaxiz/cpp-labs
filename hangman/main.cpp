#include <iostream>

#include "GameLauncher.h"

using hangman::GameLauncher;

int main() {
    try {
        hangman::GameLauncher::startGame();
    } catch (std::invalid_argument &exception) {
        std::cout << exception.what();
    }
    return 0;
}