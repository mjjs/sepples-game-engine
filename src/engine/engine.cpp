// Is this necessary?
#define GL3_PROTOTYPES = 1;

#include "engine.h"
#include "log.h"
#include "game.h"
#include "input.h"
#include "mesh.h"
#include "resourceloader.h"
#include "shader.h"
#include "transform.h"
#include "vector3.h"
#include "window.h"
#include "timer.h"

#include <chrono>
#include <cmath>
#include <memory>
#include <stdexcept>
#include <string>
#include <utility>

#include <SDL2/SDL_events.h>

namespace SGE {

Engine::Engine(const std::size_t width, const std::size_t height, const std::string& window_title) :
    rendering_engine_{width, height, window_title}
{
    Log::init();
}

void Engine::load_game(std::unique_ptr<Game> game)
{
    game_ = std::move(game);
    game_->init();
}

void Engine::render()
{
    rendering_engine_.render(*game_->root());
}

void Engine::run()
{
    if (game_ == nullptr) {
        throw std::runtime_error("No game supplied to the engine");
    }

    running_ = true;

    SDL_Event event;

    Timer timer{};
    timer.start_timer();
    unsigned int frames_rendered_this_second = 0;

    while (running_) {
        timer.update_times();

        while (SDL_PollEvent(&event) == 1) {
            if (event.type == SDL_QUIT) {
                running_ = false;
                break;
            }
        }

        Input::poll_events();

        game_->update(timer.fixed_time_step());

        while (timer.game_needs_updating()) {
            game_->fixed_update();
            timer.use_unprocessed_time();

            if (timer.has_second_passed()) {
                ENGINE_LOG_INFO("FPS: {0}", frames_rendered_this_second);
                frames_rendered_this_second = 0;
                timer.reset_seconds_spent_this_frame();
            }
        }

        render();
        frames_rendered_this_second++;
    }
}

} // namespace SGE
