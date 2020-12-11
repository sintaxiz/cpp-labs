#include <iostream>
#include "ConsoleView.h"

const std::vector<std::string> hangmen = {

        "---GAME OVER----\n"
        "  |          ||\n"
        "  O          ||\n"
        " /|\\         ||\n"
        " / \\         ||\n"
        "             ||\n"
        "           ------\n",

        "----------------\n"
        "  |          ||\n"
        "  O          ||\n"
        " /|\\         ||\n"
        " /           ||\n"
        "             ||\n"
        "           ------\n",



        "----------------\n"
        "  |          ||\n"
        "  O          ||\n"
        " /|\\         ||\n"
        "             ||\n"
        "             ||\n"
        "           ------\n",

        "----------------\n"
        "  |          ||\n"
        "  O          ||\n"
        " /|          ||\n"
        "             ||\n"
        "             ||\n"
        "           ------\n",

        "----------------\n"
        "  |          ||\n"
        "  O          ||\n"
        "  |          ||\n"
        "             ||\n"
        "             ||\n"
        "           ------\n",

        "----------------\n"
        "  |          ||\n"
        "  O          ||\n"
        "             ||\n"
        "             ||\n"
        "             ||\n"
        "           ------\n",


        "----------------\n"
        "  |          ||\n"
        "             ||\n"
        "             ||\n"
        "             ||\n"
        "             ||\n"
        "           ------\n"


};


namespace hangman {

    void ConsoleView::update() {
        if (model.isLastTurnRight()) {
            printWord();
        } else {
            printHangman();
        }
        if (model.getGameState() == GameModel::GameState::win) {
            std::cout << "You win!" << std::endl;
        }
    }

    void ConsoleView::printHangman() {
        std::cout << hangmen[model.getNumberOfTries()];

    }

    void ConsoleView::printWord() {
        std::string word = model.getWord();
        std::map<char, bool> letterMap = model.getLetterMap();
        for (auto letter : word) {
            if (letterMap[letter] == true) {
                std::cout << letter << " ";
            } else {
                std::cout << "_ ";
            }
        }
        std::cout << std::endl;
    }

    void ConsoleView::askGameMode() {
            std::cout << "Enter 1 or 2 to choose game mode:\n1. Human\n2. Bot\n";
    }

    void ConsoleView::askWord() {
        std::cout << "Enter a word" << std::endl;
    }
}

