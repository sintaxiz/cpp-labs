#include "GameLauncher.h"
#include <string>
#include <iostream>

#include "GameModel.h"
#include "GameController.h"
#include "ConsoleView.h"
#include "Human.h"
#include "Bot.h"

using hangman::GameController;
using hangman::GameModel;
using hangman::ConsoleView;
using hangman::IPlayer;
using hangman::GameLauncher;

void GameLauncher::startGame() {

    // Считывание необходимых данных с консоли для начала игры:

    ConsoleView::askGameMode();
    int mode = GameController::getGameMode();
    IPlayer *player;
    if(mode == 1) {
        player = new Human;
    }
    else if(mode == 2) {
        player = new Bot;
    } else {
        throw std::invalid_argument("Wrong input");
    }

    ConsoleView::askWord();
    std::string word;
    try {
        word = GameController::getWord();
    } catch (std::invalid_argument &exception) {
        std::cout << exception.what();
        return;
    }

    // Создание модели, а также соответствующие ей контроллер и вью
    GameModel curGame(word);

    GameController controller = GameController(curGame, *player);
    ConsoleView view = ConsoleView(curGame);

    curGame.subscribe(&view);

    controller.play();

    delete player;
}
