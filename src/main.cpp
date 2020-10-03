// Entry point for testing the Game engine

#include "engine.h"
#include "testgame.h"

#include <iostream>
#include <memory>
#include <stdexcept>

int main()
{
    try {
        SGE::Engine engine{1270, 800, "GAME"};
        engine.load_game(std::make_unique<TestGame>());
        engine.run();
    } catch (const std::runtime_error& error) {
        std::cerr << "The engine crashed: " << error.what() << '\n';
    }

    return 0;
}
