#include <iostream>
#include "game.h"

int main() {
    std::string name1, name2;
    std::cout << "Enter Player 1 name: ";
    std::cin >> name1;
    std::cout << "Enter Player 2 name: ";
    std::cin >> name2;

    Game game(name1, name2);
    game.start();

    return 0;
}
