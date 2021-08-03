// Is this necessary?
#define GL3_PROTOTYPES = 1;

#include "engine.h"
#include "event.h"
#include "eventdispatcher.h"
#include "windowcloseevent.h"
#include "log.h"
#include "game.h"
#include "input.h"
#include "timer.h"

#include <chrono>
#include <memory>
#include <stdexcept>
#include <string>

#include <SDL2/SDL_events.h>

namespace SGE {

Engine::Engine(const std::size_t width, const std::size_t height, const std::string& window_title)
{
    window_ = Window::create(window_title, width, height);
    window_->set_event_callback(BIND_EVENT_FN(Engine::handle_event));
    Log::init();
    RenderingEngine::init();
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

    Timer timer{};
    timer.start_timer();
    unsigned int frames_rendered_this_second = 0;

    while (running_) {
        timer.update_times();

        window_->update();

        game_->update(timer.fixed_time_step());

        Input::update();

        while (timer.game_needs_updating()) {
            game_->fixed_update();
            timer.use_unprocessed_time();

            if (timer.has_second_passed()) {
                LOG_INFO("FPS: {0}", frames_rendered_this_second);
                frames_rendered_this_second = 0;
                timer.reset_seconds_spent_this_frame();
            }
        }

        render();
        frames_rendered_this_second++;
    }
}

void Engine::handle_event(Event& event)
{
    EventDispatcher dispatcher(event);
    dispatcher.dispatch<WindowCloseEvent>(BIND_EVENT_FN(Engine::handle_window_close));

    if (event.is_in_category(EventCategory::INPUT)) {
        Input::handle_input_event(event);
    }
}

bool Engine::handle_window_close([[ maybe_unused ]] WindowCloseEvent& event)
{
    running_ = false;
    return true;
}

} // namespace SGE
