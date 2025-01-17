#ifndef GAMEFACTORY_H
#define GAMEFACTORY_H

#include "game.h"
#include <memory>

/**
 * @brief Abstract factory for creating games.
 */
class GameFactory {
public:
    virtual ~GameFactory() = default;
    virtual std::unique_ptr<Game> createGame(const std::string& name1, const std::string& name2) const = 0;
};

/**
 * @brief Factory for creating normal games.
 */
class NormalGameFactory : public GameFactory {
public:
    std::unique_ptr<Game> createGame(const std::string& name1, const std::string& name2) const override {
        return std::make_unique<Game>(name1, name2);
    }
};

/**
 * @brief Factory for creating timed games.
 */
class TimedGameFactory : public GameFactory {
private:
    int timeLimit;

public:
    explicit TimedGameFactory(int timeLimit) : timeLimit(timeLimit) {}

    std::unique_ptr<Game> createGame(const std::string& name1, const std::string& name2) const override {
        return std::make_unique<TimedGame>(name1, name2, timeLimit);
    }
};

#endif // GAMEFACTORY_H
