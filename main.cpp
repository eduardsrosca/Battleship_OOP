#include "game.h"
#include "clearscreen.h"
#include <iostream>
#include <memory>

int main() {
    clearScreen();
    std::cout << "Welcome to Battleships!\nChoose game mode:\n1. Simple Game\n2. Timed Game\n";
    int choice;
    std::cin >> choice;

    std::string name1, name2;
    std::cout << "Enter Player 1 name: ";
    std::cin >> name1;
    std::cout << "Enter Player 2 name: ";
    std::cin >> name2;

    std::unique_ptr<Game> game;

    if (choice == 1) {
        game = std::make_unique<Game>(name1, name2);
    } else if (choice == 2) {
        int timeLimit;
        std::cout << "Enter time limit (in seconds) for each player: ";
        std::cin >> timeLimit;
        game = std::make_unique<TimedGame>(name1, name2, timeLimit);
    } else {
        std::cout << "Invalid choice. Exiting.\n";
        return 1;
    }

    game->start();

    if (auto timedGame = dynamic_cast<TimedGame*>(game.get())) {
        std::cout << "You played a timed game!\n";
    } else {
        std::cout << "You played a simple game!\n";
    }

    return 0;
}
