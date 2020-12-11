#pragma once

namespace hangman {
    class IPlayer {
    public:
        IPlayer() = default;

        virtual ~IPlayer() = default;

        virtual char makeTurn() = 0;
    };
}
