// Is this necessary?
#define GL3_PROTOTYPES = 1;

#include "engine.h"
#include "game.h"
#include "input.h"
#include "mesh.h"
#include "resourceloader.h"
#include "shader.h"
#include "transform.h"
#include "vector3.h"
#include "window.h"

#include <chrono>
#include <cmath>
#include <iostream>

#include <SDL2/SDL.h>

bool is_input_event(const SDL_Event& event);

Engine::Engine() :
    window{window_width, window_height, window_title}
{}

void Engine::init()
{
}

void Engine::cleanup()
{
    window.cleanup();
}

void Engine::render()
{
    window.clear();
    game_.render();
    window.flip();
}

void Engine::main_loop()
{
    SDL_Event event;

    int rendered_frames = 0;
    int frame_counter = 0;

    auto previous_time = std::chrono::steady_clock::now();
    double lag = 0.0F;

    while (!exit_requested) {
        auto current_time = std::chrono::steady_clock::now();
        auto delta = std::chrono::duration_cast<std::chrono::milliseconds>(current_time - previous_time);
        previous_time = current_time;

        lag += static_cast<double>(delta.count());

        while (SDL_PollEvent(&event) == 1) {
            if (event.type == SDL_QUIT) {
                exit_requested = true;
                break;
            }

            if (is_input_event(event)) {
                input.key_event(event);
            }
        }

        frame_counter += delta.count();

        game_.input();

        while (lag >= 16) {
            game_.update();
            lag -= 16;

            if (frame_counter >= 1000) {
                std::cout << "FPS: " << rendered_frames << '\n';
                rendered_frames = 0;
                frame_counter = 0;
            }
        }

        render();
        rendered_frames++;

        // Handle game input before input.update();
        input.update();
    }
}

bool is_input_event(const SDL_Event& event)
{
    switch (event.type) {
    case SDL_KEYDOWN:
    case SDL_KEYUP:
    case SDL_MOUSEBUTTONDOWN:
    case SDL_MOUSEBUTTONUP:
    case SDL_MOUSEMOTION:
        return true;
    }

    return false;
}
