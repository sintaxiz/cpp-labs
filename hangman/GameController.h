#pragma once

#include <string>

#include "GameModel.h"
#include "IPlayer.h"

namespace hangman {
    class GameController {
    public:
        GameController(GameModel &model, IPlayer &player) : model(model), player(player)  {};
        ~GameController() = default;

        void play();

        static std::string getWord();
        static int getGameMode();
    private:
        GameModel &model;
        IPlayer &player;
    };
}




