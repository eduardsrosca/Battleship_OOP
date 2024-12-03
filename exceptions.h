#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <exception>

/// Custom exception for game errors.
class GameException : public std::exception {
public:
    [[nodiscard]] const char* what() const noexcept override;
};

/// Exception for ship placement errors.
class ShipPlacementException : public GameException {
public:
    [[nodiscard]] const char* what() const noexcept override;
};

/// Exception for invalid attack errors.
class InvalidAttackException : public GameException {
public:
    [[nodiscard]] const char* what() const noexcept override;
};

#endif // EXCEPTIONS_H
