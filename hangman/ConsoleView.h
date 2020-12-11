#pragma once

#include "GameModel.h"
#include "IObserver.h"

namespace hangman {
    class ConsoleView : public IObserver {
    public:
        ConsoleView(GameModel &model) : model(model) {} ;
        ~ConsoleView() override = default;

        void update() override;

        static void askGameMode();
        static void askWord();

    private:
        GameModel &model;
        void printWord();
        void printHangman();
    };
}




