#include "board.h"
#include <iostream>
#include <iomanip>

Board::Board() : grid(10, 10, '~'), hitStatus(10, 10, false) {}

Board::Board(const Board& other) : grid(other.grid), hitStatus(other.hitStatus) {}

Board::~Board() = default;

Board& Board::operator=(const Board& other) {
    if (this != &other) {
        grid = other.grid;
        hitStatus = other.hitStatus;
    }
    return *this;
}

bool Board::placeShip(int startRow, int startCol, char orientation, char symbol, int size) {
    for (int i = 0; i < size; ++i) {
        int r = (orientation == 'H') ? startRow : startRow + i;
        int c = (orientation == 'H') ? startCol + i : startCol;
        if (r >= grid.getRows() || c >= grid.getCols() || grid.get(r, c) != '~')
            return false;
    }

    for (int i = 0; i < size; ++i) {
        int r = (orientation == 'H') ? startRow : startRow + i;
        int c = (orientation == 'H') ? startCol + i : startCol;
        grid.set(r, c, symbol);
    }
    return true;
}

bool Board::attack(int row, int col) {
    if (hitStatus.get(row, col)) return false;

    hitStatus.set(row, col, true);

    if (grid.get(row, col) != '~') {
        grid.set(row, col, 'X'); // Hit
        return true;
    } else {
        grid.set(row, col, 'O'); // Miss
        return false;
    }
}

char Board::getCell(int row, int col) const {
    return grid.get(row, col);
}

bool Board::isShipSunk(int row, int col) const {
    char symbol = grid.get(row, col);
    for (int r = 0; r < grid.getRows(); ++r) {
        for (int c = 0; c < grid.getCols(); ++c) {
            if (grid.get(r, c) == symbol) {
                return false;
            }
        }
    }
    return true;
}

bool Board::allShipsSunk() const {
    for (int r = 0; r < grid.getRows(); ++r) {
        for (int c = 0; c < grid.getCols(); ++c) {
            char cell = grid.get(r, c);
            if (cell != '~' && cell != 'O' && cell != 'X') {
                return false;
            }
        }
    }
    return true;
}

void Board::display(bool showShips) const {
    std::cout << "  ";
    for (char c = 'A'; c < 'A' + grid.getCols(); ++c) {
        std::cout << std::setw(2) << c;
    }
    std::cout << "\n";

    for (int i = 0; i < grid.getRows(); ++i) {
        std::cout << std::setw(2) << i + 1 << " ";
        for (int j = 0; j < grid.getCols(); ++j) {
            if (showShips || hitStatus.get(i, j)) {
                std::cout << grid.get(i, j) << " ";
            } else {
                std::cout << "~ ";
            }
        }
        std::cout << "\n";
    }
}
