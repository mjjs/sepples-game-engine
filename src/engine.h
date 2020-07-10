#ifndef _GE_ENGINE_H
#define _GE_ENGINE_H

#include "game.h"
#include "input.h"
#include "window.h"

#include <cstddef>
#include <string>

class Engine {
    private:
        // TODO: Get these from config file
        const std::size_t window_width = 800;
        const std::size_t window_height = 600;
        const std::string window_title = "Sepples game engine";

        bool exit_requested = false;

        Input input;
        Window window;

        void render();

        // For testing the engine
        Game::Game game_;

    public:
        Engine();
        void init();
        void cleanup();

        void main_loop();
};
#endif
