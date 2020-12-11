#pragma once

#include <string>
#include <map>
#include <functional>
#include <list>

#include "IObserver.h"
#include "IPlayer.h"


namespace hangman {

    class GameModel {
    public:
        ~GameModel() = default;

        GameModel(std::string word);

        void tryLetter(char letter);

        enum class GameState {play, win, lose};
        GameState getGameState();

        int getNumberOfTries();

        std::string getWord() {
            return currentWord;
        }
        std::map<char, bool> getLetterMap() {
            return isGuessedLetter;
        }

        bool isLastTurnRight() {
            return isRightTurn;
        }

        void subscribe(IObserver *observer);
        void unsubscribe(IObserver *observer);

    private:
        int numberOfTries;
        int remainingLetters;
        GameState gameState;
        std::string currentWord;
        bool isRightTurn{};

        std::map<char, bool> isGuessedLetter;

        std::list<IObserver *> subscribers;
        void notify() const;

    };
}
