#include <iostream>
#include <vector>
#include <string>

class Ship {
private:
    std::string name;
    char symbol; // simbol pentru barca
    int size;
    bool* hitPositions;
    int startRow;
    int startCol;
    char orientation;

public:
    Ship(const std::string& name, char symbol, int size)
        : name(name), symbol(symbol), size(size), startRow(-1), startCol(-1), orientation('H') {
        hitPositions = new bool[size] {false};
    }

    Ship(const Ship& other)
        : name(other.name), symbol(other.symbol), size(other.size), startRow(other.startRow), startCol(other.startCol), orientation(other.orientation) {
        hitPositions = new bool[size];
        for (int i = 0; i < size; i++) {
            hitPositions[i] = other.hitPositions[i];
        }
    }

    Ship& operator=(const Ship& other) {
        if (this == &other) return *this;

        delete[] hitPositions;

        name = other.name;
        symbol = other.symbol;
        size = other.size;
        startRow = other.startRow;
        startCol = other.startCol;
        orientation = other.orientation;

        hitPositions = new bool[size];
        for (int i = 0; i < size; i++) {
            hitPositions[i] = other.hitPositions[i];
        }

        return *this;
    }

    ~Ship() {
        delete[] hitPositions;
    }

    int getSize() const {
        return size;
    }

    char getSymbol() const {
        return symbol;
    }

    void setPosition(int row, int col, char orientation) {
        startRow = row;
        startCol = col;
        this->orientation = orientation;
    }

    bool registerHit(int row, int col) {
        int hitIndex = (orientation == 'H') ? col - startCol : row - startRow;
        if (hitIndex >= 0 && hitIndex < size) {
            hitPositions[hitIndex] = true;
            return true;
        }
        return false;
    }

    bool isSunk() const {
        for (int i = 0; i < size; ++i) {
            if (!hitPositions[i]) return false;
        }
        return true;
    }

    friend std::ostream& operator<<(std::ostream& os, const Ship& ship) {
        os << ship.name << " (Size: " << ship.size << ")";
        return os;
    }
};

class Board {
private:
    std::vector<std::vector<char>> grid;
    std::vector<Ship> ships;

public:
    Board() : grid(10, std::vector<char>(10, '~')) {}

    bool placeShip(Ship& ship, int row, int col, char orientation) {
        int size = ship.getSize();
        for (int i = 0; i < size; ++i) {
            int r = (orientation == 'H') ? row : row + i;
            int c = (orientation == 'H') ? col + i : col;
            if (r >= 10 || c >= 10 || grid[r][c] != '~')
                return false;
        }

        for (int i = 0; i < size; ++i) {
            int r = (orientation == 'H') ? row : row + i;
            int c = (orientation == 'H') ? col + i : col;
            grid[r][c] = ship.getSymbol();
        }
        ship.setPosition(row, col, orientation);
        ships.push_back(ship);
        return true;
    }

    bool attack(int row, int col) {
        if (grid[row][col] != '~' && grid[row][col] != 'O') {
            grid[row][col] = 'X'; // hit
            return true;
        } else if (grid[row][col] == '~') {
            grid[row][col] = 'O'; // miss
            return false;
        }
        return false; // deja atacat
    }

    bool allShipsSunk() const {
        for (const auto& ship : ships) {
            if (!ship.isSunk()) return false;
        }
        return true;
    }

    void display(bool showShips = false) const {
        std::cout << "  ";
        for (char c = 'A'; c < 'A' + 10; ++c) {
            std::cout << c << " ";
        }
        std::cout << std::endl;

        for (int i = 0; i < 10; ++i) {
            std::cout << i + 1 << " ";
            for (int j = 0; j < 10; ++j) {
                if (showShips) {
                    std::cout << grid[i][j] << " ";
                } else {
                    std::cout << (grid[i][j] == '~' ? '~' : grid[i][j]) << " ";
                }
            }
            std::cout << std::endl;
        }
    }
};

class Player {
private:
    std::string name;
    Board board;

public:
    Player(const std::string& name) : name(name) {}

    std::string getName() const {
        return name;
    }

    Board& getBoard() {
        return board;
    }

    void placeShips() {
        std::vector<Ship> ships = {
            Ship("Carrier", 'C', 5),
            Ship("Battleship", 'B', 4),
            Ship("Destroyer", 'D', 3),
            Ship("Submarine", 'S', 3),
            Ship("Patrol Boat", 'P', 2)
        };

        for (const auto& ship : ships) {
            int row, col;
            char orientation;
            bool placed = false;
            while (!placed) {
                std::cout << name << ", place your " << ship << " (size " << ship.getSize() << ")\n";
                std::cout << "Enter row (1-10): ";
                std::cin >> row;
                std::cout << "Enter column (A-J): ";
                char colChar;
                std::cin >> colChar;
                col = colChar - 'A';

                std::cout << "Enter orientation (H/V): ";
                std::cin >> orientation;
                orientation = toupper(orientation);

                // Validare input
                if (row < 1 || row > 10 || col < 0 || col > 9 || (orientation != 'H' && orientation != 'V')) {
                    std::cout << "Invalid input. Try again.\n";
                    continue;
                }
                placed = board.placeShip(const_cast<Ship&>(ship), row - 1, col, orientation);
                if (!placed) {
                    std::cout << "Cannot place ship there. Try again.\n";
                } else {
                    board.display(true); // Afișează tabla cu bărcile plasate
                }
            }
        }
    }

    bool takeTurn(Player& opponent) {
        int row, col;
        while (true) {
            std::cout << name << ", enter your attack coordinates (row and column):\n";
            std::cout << "Row (1-10): ";
            std::cin >> row;
            std::cout << "Column (A-J): ";
            char colChar;
            std::cin >> colChar;
            col = colChar - 'A';

            // Validare input
            if (row < 1 || row > 10 || col < 0 || col > 9) {
                std::cout << "Invalid input. Try again.\n";
                continue;
            }
            if (opponent.getBoard().attack(row - 1, col)) {
                std::cout << "Hit!\n";
                return true;
            } else {
                std::cout << "Miss!\n";
                return false;
            }
        }
    }

    void displayBoard(bool showShips = false) const {
        board.display(showShips);
    }
};

class Game {
private:
    Player player1;
    Player player2;

public:
    Game(const std::string& name1, const std::string& name2)
        : player1(name1), player2(name2) {}

    void start() {
        player1.placeShips();
        player2.placeShips();

        bool game_over = false;
        Player* currentPlayer = &player1;
        Player* opponent = &player2;

        while (!game_over) {
            std::cout << "\n" << currentPlayer->getName() << "'s turn:\n";
            currentPlayer->displayBoard(false);
            opponent->displayBoard(true);
            if (currentPlayer->takeTurn(*opponent)) {
                if (opponent->getBoard().allShipsSunk()) {
                    std::cout << currentPlayer->getName() << " wins!\n";
                    game_over = true;
                }
            } else {
                std::swap(currentPlayer, opponent);
            }
        }
    }
};

int main() {
    std::string player1Name, player2Name;
    std::cout << "Enter Player 1 name: ";
    std::cin >> player1Name;
    std::cout << "Enter Player 2 name: ";
    std::cin >> player2Name;

    Game game(player1Name, player2Name);
    game.start();

    return 0;
}