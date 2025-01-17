#include "gamefactory.h"
#include <iostream>
#include <memory>

int main() {
    std::unique_ptr<GameFactory> factory;

    std::cout << "Welcome to Battleships!\n";
    std::cout << "Game modes:\n 1 - Normal gameplay\n 2 - Timed gameplay\nSelect: ";
    int choice;
    std::cin >> choice;

    if (choice == 1) {
        factory = std::make_unique<NormalGameFactory>();
    } else if (choice == 2) {
        const int timeLimit = 210;
        factory = std::make_unique<TimedGameFactory>(timeLimit);
    } else {
        std::cerr << "Invalid choice!\n";
        return 1;
    }

    std::string name1, name2;
    std::cout << "Enter Player 1 name: ";
    std::cin >> name1;
    std::cout << "Enter Player 2 name: ";
    std::cin >> name2;

    auto game = factory->createGame(name1, name2);
    game->start();

    if (auto timedGame = dynamic_cast<TimedGame*>(game.get())) {
        std::cout << "You played a timed game!\n";
    } else {
        std::cout << "You played a simple game!\n";
    }

    return 0;
}
