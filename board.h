#ifndef BOARD_H
#define BOARD_H

#include "grid.h"

/**
 * @class Board
 * @brief Represents the player's game board for Battleship.
 */
class Board {
private:
    /**
     * @brief The grid representing the board with characters for ships and empty spaces.
     */
    Grid<char> grid;

    /**
     * @brief The grid indicating hit/miss status for each cell.
     */
    Grid<bool> hitStatus;

public:
    /**
     * @brief Default constructor for the Board class.
     */
    Board();

    /**
     * @brief Copy constructor for the Board class.
     * @param other The Board instance to copy from.
     */
    Board(const Board& other);

    /**
     * @brief Destructor for the Board class.
     */
    ~Board();

    /**
     * @brief Assignment operator for the Board class.
     * @param other The Board instance to assign from.
     * @return Reference to the assigned Board instance.
     */
    Board& operator=(const Board& other);

    /**
     * @brief Places a ship on the board.
     * @param startRow The starting row of the ship.
     * @param startCol The starting column of the ship.
     * @param orientation The orientation of the ship ('H' for horizontal, 'V' for vertical).
     * @param symbol The character symbol representing the ship.
     * @param size The size of the ship.
     * @return True if the ship was placed successfully, false otherwise.
     */
    bool placeShip(int startRow, int startCol, char orientation, char symbol, int size);

    /**
     * @brief Attacks a cell on the board.
     * @param row The row of the cell to attack.
     * @param col The column of the cell to attack.
     * @return True if the attack hit a ship, false otherwise.
     */
    bool attack(int row, int col);

    /**
     * @brief Gets the character at a specific cell on the board.
     * @param row The row of the cell.
     * @param col The column of the cell.
     * @return The character at the specified cell.
     */
    [[nodiscard]] char getCell(int row, int col) const;

    /**
     * @brief Checks if the ship at a specific cell is sunk.
     * @param row The row of the cell.
     * @param col The column of the cell.
     * @return True if the ship is sunk, false otherwise.
     */
    [[nodiscard]] bool isShipSunk(int row, int col) const;

    /**
     * @brief Checks if all ships on the board are sunk.
     * @return True if all ships are sunk, false otherwise.
     */
    [[nodiscard]] bool allShipsSunk() const;

    /**
     * @brief Displays the board.
     * @param showShips If true, displays the ships; otherwise, hides them.
     */
    void display(bool showShips) const;
};

#endif // BOARD_H
