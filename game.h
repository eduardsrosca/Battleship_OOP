#ifndef GAME_H
#define GAME_H

#include "player.h"
#include <string>
#include <iostream>
#include <chrono>
#include <thread>
#include <utility>

/**
 * @class Game
 * @brief Manages the overall game flow.
 */
class Game {
protected:
    Player player1;
    Player player2;

public:
    Game(std::string name1, std::string name2);

    /**
     * @brief Starts the game, including ship placement and game loop.
     */
    virtual void start();

    virtual ~Game() = default;
};

/**
 * @class TimedGame
 * @brief Derived class that adds a timer for each player.
 */
class TimedGame : public Game {
private:
    int timeLimit;

public:
    TimedGame(std::string name1, std::string name2, int timeLimit);

    /**
     * @brief Starts the timed game.
     */
    void start() override;
};

#endif // GAME_H
