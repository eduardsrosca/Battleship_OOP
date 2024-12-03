#include "game.h"
#include "exceptions.h"
#include "clearscreen.h"
#include <iostream>

Game::Game(std::string name1, std::string name2)
    : player1(std::move(name1)), player2(std::move(name2)) {}

void Game::start() {
    clearScreen();
    player1.placeShips();
    clearScreen();
    player2.placeShips();
    clearScreen();

    bool gameOver = false;
    Player* currentPlayer = &player1;
    Player* opponent = &player2;

    while (!gameOver) {
        try {
            gameOver = currentPlayer->takeTurn(*opponent);
            if (!gameOver) {
                std::swap(currentPlayer, opponent);
            }
        } catch (const GameException& e) {
            std::cerr << e.what() << std::endl;
            return;
        }
    }

    std::cout << currentPlayer->getName() << " wins!\n";
}
