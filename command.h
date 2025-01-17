#ifndef COMMAND_H
#define COMMAND_H

#include "board.h"
#include "exceptions.h"
#include <memory>

/**
 * @brief Abstract command class.
 */
class Command {
public:
    virtual ~Command() = default;
    virtual void execute() = 0;
    virtual void undo() = 0;
};

/**
 * @brief Command for placing ships.
 */
class PlaceShipCommand : public Command {
private:
    Board& board;
    int row, col;
    char orientation;
    char symbol;
    int size;
    bool placed;

public:
    PlaceShipCommand(Board& board, int row, int col, char orientation, char symbol, int size)
        : board(board), row(row), col(col), orientation(orientation), symbol(symbol), size(size), placed(false) {}

    void execute() override {
        placed = board.placeShip(row, col, orientation, symbol, size);
        if (!placed) {
            throw ShipPlacementException();
        }
    }

    void undo() override {
        if (placed) {
            for (int i = 0; i < size; ++i) {
                int r = (orientation == 'H') ? row : row + i;
                int c = (orientation == 'H') ? col + i : col;
                board.attack(r, c);
            }
        }
    }
};

/**
 * @brief Command for attacking.
 */
class AttackCommand : public Command {
private:
    Board& board;
    int row, col;
    bool hit;

public:
    AttackCommand(Board& board, int row, int col) : board(board), row(row), col(col), hit(false) {}

    void execute() override {
        hit = board.attack(row, col);
    }

    void undo() override {
    }
};

#endif // COMMAND_H
