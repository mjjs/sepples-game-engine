// Is this necessary?
#define GL3_PROTOTYPES = 1;

#include "engine.h"
#include "game.h"
#include "input.h"
#include "inputaction.h"
#include "mesh.h"
#include "resourceloader.h"
#include "shader.h"
#include "transform.h"
#include "vector3.h"
#include "window.h"

#include <chrono>
#include <cmath>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <utility>

#include <SDL2/SDL.h>

bool is_input_event(const SDL_Event& event);

SGE::Engine::Engine(const std::size_t width, const std::size_t height, const std::string& window_title) :
    rendering_engine_{width, height, window_title}
{
}

void SGE::Engine::load_game(std::unique_ptr<Game::Game> game)
{
    game_ = std::move(game);
}

void SGE::Engine::render()
{
    rendering_engine_.render(*game_->root());
}

void SGE::Engine::run()
{
    if (game_ == nullptr) {
        throw std::runtime_error("No game supplied to the engine");
    }

    running_ = true;

    SDL_Event event;

    const int ms_per_second = 1000;
    const float seconds_per_frame = .16F;
    int frames_rendered_this_second = 0;
    float frame_time = 0;

    auto previous_time = std::chrono::steady_clock::now();
    float unprocessed_time = 0.0F;

    while (running_) {
        auto current_time = std::chrono::steady_clock::now();
        auto elapsed_time =
            std::chrono::duration_cast<std::chrono::milliseconds>(current_time - previous_time);

        previous_time = current_time;

        float delta = static_cast<float>(elapsed_time.count()) / ms_per_second;
        unprocessed_time += delta;

        while (SDL_PollEvent(&event) == 1) {
            if (event.type == SDL_QUIT) {
                running_ = false;
                break;
            }

            if (is_input_event(event)) {
                input_.key_event(event);
            }
        }

        frame_time += delta;

        // Handle game input before input.update();
        game_->input(input_);
        input_.update();

        while (unprocessed_time > seconds_per_frame) {
            game_->update();
            unprocessed_time -= seconds_per_frame;

            if (frame_time >= 1.0F) {
                std::cout << "FPS: " << frames_rendered_this_second << '\n';
                frames_rendered_this_second = 0;
                frame_time = 0;
            }
        }

        render();
        frames_rendered_this_second++;
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
