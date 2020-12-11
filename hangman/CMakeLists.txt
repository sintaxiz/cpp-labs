cmake_minimum_required(VERSION 3.14)
project(hangman)

set(CMAKE_CXX_STANDARD 20)

add_executable(hangman main.cpp GameModel.cpp Human.cpp GameController.cpp GameController.h ConsoleView.cpp ConsoleView.h IObserver.h IPlayer.h Bot.cpp Bot.h GameLauncher.cpp GameLauncher.h)