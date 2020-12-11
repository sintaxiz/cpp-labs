#pragma once

#include "IPlayer.h"
#include "GameModel.h"

class Bot : public hangman::IPlayer {
public:
    Bot();
    ~Bot() = default;
    char makeTurn() override;

private:
    std::vector<char> alphabet;
    int currentLetter;
};



