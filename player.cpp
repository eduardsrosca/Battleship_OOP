#include "player.h"
#include "clearscreen.h"
#include <iostream>
#include <limits>
#include <cctype>
#include "exceptions.h"

Player::Player(std::string playerName) : name(std::move(playerName)) {}

std::string Player::getName() const { return name; }

std::pair<int, int> Player::getValidatedCoordinates() {
    int row, col;
    char colChar;
    while (true) {
        std::cout << "Enter row (1-10): ";
        std::cin >> row;

        if (std::cin.fail() || row < 1 || row > 10) {
            std::cout << "Invalid row. Must be a number between 1 and 10.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        std::cout << "Enter column (A-J): ";
        std::cin >> colChar;
        colChar = toupper(colChar);
        col = colChar - 'A';

        if (col < 0 || col >= 10) {
            std::cout << "Invalid column. Must be between A and J.\n";
            continue;
        }
        break;
    }
    return {row - 1, col};
}

char Player::getValidatedOrientation() {
    char orientation;
    while (true) {
        std::cout << "Enter orientation (H/V): ";
        std::cin >> orientation;
        orientation = toupper(orientation);
        if (orientation == 'H' || orientation == 'V') {
            break;
        }
        std::cout << "Invalid orientation. Must be 'H' or 'V'.\n";
    }
    return orientation;
}

void Player::placeShips() {
    std::vector<std::pair<std::string, int>> ships = {
        {"Carrier", 5}, {"Battleship", 4}, {"Destroyer", 3},
        {"Submarine", 3}, {"Patrol Boat", 2}
    };

    for (const auto& ship : ships) {
        bool placed = false;

        while (!placed) {
            std::cout << name << ", place your " << ship.first << " (size " << ship.second << "):\n";
            ownBoard.display(true);

            auto [row, col] = getValidatedCoordinates();
            char orientation = getValidatedOrientation();

            placed = ownBoard.placeShip(row, col, orientation, static_cast<char>(ship.first[0]), ship.second);
            if (!placed) {
                std::cout << "Invalid position. Try again.\n";
            }
        }
        clearScreen();
    }
}

bool Player::takeTurn(Player& opponent) {
    bool continueTurn = false;

    do {
        std::cout << name << "'s turn:\n";
        std::cout << "Opponent's board:\n";
        attackBoard.display(false);
        std::cout << "Your own board:\n";
        ownBoard.display(true);

        auto [row, col] = getValidatedCoordinates();

        bool hit = opponent.ownBoard.attack(row, col);
        attackBoard.attack(row, col);

        if (hit) {
            std::cout << "Hit!\n";
            if (opponent.ownBoard.isShipSunk(row, col)) {
                std::cout << "You sunk a ship!\n";
                continueTurn = false;
            } else {
                continueTurn = true;
            }
        } else {
            std::cout << "Miss!\n";
            continueTurn = false;
        }
    } while (continueTurn);

    return opponent.ownBoard.allShipsSunk();
}
