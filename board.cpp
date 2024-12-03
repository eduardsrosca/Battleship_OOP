#include "board.h"
#include <iostream>
#include <iomanip>

Board::Board() : grid(10, std::vector<char>(10, '~')), hitStatus(10, std::vector<bool>(10, false)) {}

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
        if (r >= 10 || c >= 10 || grid[r][c] != '~')
            return false;
    }

    for (int i = 0; i < size; ++i) {
        int r = (orientation == 'H') ? startRow : startRow + i;
        int c = (orientation == 'H') ? startCol + i : startCol;
        grid[r][c] = symbol;
    }
    return true;
}

bool Board::attack(int row, int col) {
    if (hitStatus[row][col]) return false;

    hitStatus[row][col] = true;

    if (grid[row][col] != '~') {
        grid[row][col] = 'X'; // Hit
        return true;
    } else {
        grid[row][col] = 'O'; // Miss
        return false;
    }
}

char Board::getCell(int row, int col) const {
    return grid[row][col];
}

bool Board::isShipSunk(int row, int col) const {
    char symbol = grid[row][col];
    for (const auto& singleRow : grid) {
        for (char cell : singleRow) {
            if (cell == symbol) {
                return false;
            }
        }
    }
    return true;
}

bool Board::allShipsSunk() const {
    for (const auto& singleRow : grid) {
        for (char cell : singleRow) {
            if (cell != '~' && cell != 'O' && cell != 'X') {
                return false;
            }
        }
    }
    return true;
}

void Board::display(bool showShips) const {
    std::cout << "  ";
    for (char c = 'A'; c < 'A' + 10; ++c) {
        std::cout << std::setw(2) << c;
    }
    std::cout << "\n";

    for (int i = 0; i < 10; ++i) {
        std::cout << std::setw(2) << i + 1 << " ";
        for (int j = 0; j < 10; ++j) {
            if (showShips || hitStatus[i][j]) {
                std::cout << grid[i][j] << " ";
            } else {
                std::cout << "~ ";
            }
        }
        std::cout << "\n";
    }
}
