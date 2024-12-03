#include "exceptions.h"

const char* GameException::what() const noexcept {
    return "An error occurred in the game!";
}

const char* ShipPlacementException::what() const noexcept {
    return "Ship placement error!";
}

const char* InvalidAttackException::what() const noexcept {
    return "Invalid attack coordinates!";
}
