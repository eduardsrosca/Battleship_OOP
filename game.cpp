#include "game.h"
#include "exceptions.h"
#include "clearscreen.h"
#include <iostream>
#include <chrono>
#include <thread>

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
            clearScreen();
            std::swap(currentPlayer, opponent);
        } catch (const std::exception& e) {
            std::cout << e.what() << "\n";
        }
    }
}

TimedGame::TimedGame(std::string name1, std::string name2, int timeLimit)
    : Game(std::move(name1), std::move(name2)), timeLimit(timeLimit) {}

void TimedGame::start() {
    clearScreen();
    player1.placeShips();
    clearScreen();
    player2.placeShips();
    clearScreen();

    int player1Time = timeLimit;
    int player2Time = timeLimit;

    bool gameOver = false;
    Player* currentPlayer = &player1;
    Player* opponent = &player2;
    int* currentTime = &player1Time;
    int* opponentTime = &player2Time;

    while (!gameOver) {
        auto startTurn = std::chrono::steady_clock::now();

        try {
            std::cout << currentPlayer->getName() << "'s turn. Remaining time: " << *currentTime << " seconds.\n";
            gameOver = currentPlayer->takeTurn(*opponent);
            clearScreen();
        } catch (const std::exception& e) {
            std::cout << e.what() << "\n";
        }

        auto endTurn = std::chrono::steady_clock::now();
        *currentTime -= std::chrono::duration_cast<std::chrono::seconds>(endTurn - startTurn).count();

        if (*currentTime <= 0) {
            std::cout << currentPlayer->getName() << " ran out of time! " << opponent->getName() << " wins!\n";
            break;
        }

        std::swap(currentPlayer, opponent);
        std::swap(currentTime, opponentTime);
    }
}
