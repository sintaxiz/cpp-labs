#include <iostream>
#include "GameController.h"

void hangman::GameController::play() {
    // игрок делает ходы, пока игра не закончилась
    while(model.getGameState() == GameModel::GameState::play) {
        char letter = player.makeTurn();
        if (letter >= 'a' && letter <= 'z') {
            model.tryLetter(letter);
        } else {
            std::cout << "Wrong letter" << std::endl;
        }
    }
}

std::string hangman::GameController::getWord() {
    std::string word;
    std::cin >> word;
    for (auto letter : word) {
        if (letter < 'a' || letter > 'z') {
            throw std::invalid_argument("Wrong word");
        }
    }
    return word;
}

int hangman::GameController::getGameMode() {
    int mode;
    std::cin >> mode;
    return mode;
}
