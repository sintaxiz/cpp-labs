#include <string>

#include "GameModel.h"

namespace hangman {
    GameModel::GameModel(std::string word) {
        currentWord = word;
        numberOfTries = 6;
        gameState = GameState::play;
        for (auto letter : word) {
            isGuessedLetter[letter] = false;
        }
        remainingLetters = isGuessedLetter.size();
    }

    void GameModel::tryLetter(char letter) {
        if (isGuessedLetter.find(letter) != isGuessedLetter.end()) {
            isGuessedLetter[letter] = true;
            remainingLetters -= isGuessedLetter.count(letter);
            isRightTurn = true;
        } else {
            numberOfTries--;
            isRightTurn = false;
        }
        if (numberOfTries == 0) {
            gameState = GameState::lose;
        }
        if (remainingLetters == 0) {
            gameState = GameState::win;
        }
        notify();
    }

    void GameModel::notify() const {
        for (auto sub : subscribers) {
            sub->update();
        }
    }

    void GameModel::subscribe(IObserver *observer) {
        subscribers.push_back(observer);
    }

    void GameModel::unsubscribe (IObserver *observer) {
        subscribers.remove(observer);
    }

    GameModel::GameState GameModel::getGameState() {
        return gameState;
    }

    int GameModel::getNumberOfTries() {
        return numberOfTries;
    }
}

