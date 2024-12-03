#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include "board.h"

/**
 * @class Player
 * @brief Represents a player in the game.
 */

class Player {
private:
    std::string name;
    Board ownBoard;
    Board attackBoard;

    /**
     * @brief Prompts the player to input coordinates and validates them.
     * @return A pair containing the validated row and column.
     */

    static std::pair<int, int> getValidatedCoordinates();

    /**
     * @brief Prompts the player to input ship orientation and validates it.
     * @return The validated orientation character ('H' or 'V').
     */

    static char getValidatedOrientation();

public:
    explicit Player(std::string playerName);
    [[nodiscard]] std::string getName() const;

    /**
     * @brief Allows the player to place their ships on the board.
     */

    void placeShips();

    /**
     * @brief Allows the player to take their turn and attack the opponent's board.
     * @param opponent The opponent player.
     * @return true if all opponent's ships are sunk, false otherwise.
     */

    bool takeTurn(Player& opponent);
};

#endif // PLAYER_H
