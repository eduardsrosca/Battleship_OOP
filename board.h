#ifndef BOARD_H
#define BOARD_H

#include <vector>

/**
 * @class Board
 * @brief Represents the player's game board for Battleship.
 */

class Board {
private:
    std::vector<std::vector<char>> grid;
    std::vector<std::vector<bool>> hitStatus;

public:
    Board();
    Board(const Board& other);
    ~Board();
    Board& operator=(const Board& other);

    /**
     * @brief Attempts to place a ship on the board.
     * @param startRow The starting row for the ship.
     * @param startCol The starting column for the ship.
     * @param orientation The orientation of the ship ('H' for horizontal, 'V' for vertical).
     * @param symbol The symbol representing the ship.
     * @param size The size of the ship.
     * @return true if the ship was placed successfully, false otherwise.
     */

    bool placeShip(int startRow, int startCol, char orientation, char symbol, int size);

    /**
     * @brief Executes an attack on a cell.
     * @param row The row of the attack.
     * @param col The column of the attack.
     * @return true if the attack hit a ship, false if it missed.
     */

    bool attack(int row, int col);
    [[nodiscard]] char getCell(int row, int col) const;

    /**
     * @brief Checks if the ship at the given coordinates is sunk.
     * @param row The row of the ship.
     * @param col The column of the ship.
     * @return true if the ship is sunk, false otherwise.
     */

    [[nodiscard]] bool isShipSunk(int row, int col) const;

    /**
     * @brief Checks if all ships have been sunk on the board.
     * @return true if all ships are sunk, false otherwise.
     */

    [[nodiscard]] bool allShipsSunk() const;

    /**
     * @brief Displays the board to the console.
     * @param showShips If true, shows ships; otherwise, hides them.
     */

    void display(bool showShips) const;
};

#endif // BOARD_H
