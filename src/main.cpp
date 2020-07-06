#include "engine.h"

#include <iostream>
#include <stdexcept>

int main()
{
    try {
        Engine engine{};
        engine.init();
        engine.main_loop();
        engine.cleanup();
    } catch (const std::runtime_error& error) {
        std::cerr << error.what() << '\n';
    }

    return 0;
}
