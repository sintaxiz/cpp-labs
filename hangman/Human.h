#pragma once

#include "IPlayer.h"
#include "GameModel.h"

class Human : public hangman::IPlayer {
public:
    Human() = default;
    ~Human() = default;
    char makeTurn() override;
};



