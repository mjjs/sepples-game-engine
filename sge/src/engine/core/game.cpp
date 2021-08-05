#include "engine/core/game.h"

#include "engine/event/eventdispatcher.h"
#include "engine/core/log.h"
#include "engine/core/timer.h"
#include "engine/rendering/window.h"
#include "engine/event/windowcloseevent.h"

#include <memory>

namespace SGE
{

Game* Game::instance_ = nullptr; // NOLINT

Game::Game()
{
    instance_ = this;

    window_ = Window::create();
    window_->set_event_callback(BIND_EVENT_FN(Game::handle_event));

    Log::init();
    RenderingEngine::init();
}

void Game::run()
{
    Timer timer{};

    timer.start_timer();
    unsigned int frames_rendered_this_second = 0;

    while (running_) {
        timer.update_times();

        window_->update();

        update(timer.fixed_time_step());

        Input::update();

        while (timer.game_needs_updating()) {
            fixed_update();
            timer.use_unprocessed_time();

            if (timer.has_second_passed()) {
                LOG_INFO("FPS: {0}", frames_rendered_this_second);
                frames_rendered_this_second = 0;
                timer.reset_seconds_spent_this_frame();
            }
        }

        frames_rendered_this_second++;
    }
}

void Game::handle_event(Event& event)
{
    EventDispatcher dispatcher(event);
    dispatcher.dispatch<WindowCloseEvent>(
        BIND_EVENT_FN(Game::handle_window_close));

    if (event.is_in_category(EventCategory::INPUT)) {
        Input::handle_input_event(event);
    }
}

bool Game::handle_window_close([[maybe_unused]] WindowCloseEvent& event)
{
    running_ = false;
    return true;
}

} // namespace SGE

int main(int argc, char** argv)
{
    auto game = SGE::CreateGame(argc, argv);
    game->run();
}
