#ifndef GAME_H
#define GAME_H

#include "player.h"

/**
 * @class Game
 * @brief Manages the overall game flow.
 */


class Game {
private:
    Player player1;
    Player player2;

public:
    Game(std::string name1, std::string name2);

    /**
     * @brief Starts the game, including ship placement and game loop.
     */

    void start();
};

#endif // GAME_H
