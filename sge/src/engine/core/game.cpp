#include "game.h"
#include "eventdispatcher.h"
#include "log.h"
#include "window.h"
#include "windowcloseevent.h"
#include "timer.h"

#include <memory>

namespace SGE {

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
    dispatcher.dispatch<WindowCloseEvent>(BIND_EVENT_FN(Game::handle_window_close));

    if (event.is_in_category(EventCategory::INPUT)) {
        Input::handle_input_event(event);
    }
}

bool Game::handle_window_close([[ maybe_unused ]] WindowCloseEvent& event)
{
    running_ = false;
    return true;
}

// OLD API TO BE REMOVED

void Game::render(Shader& shader, const RenderingEngine& rendering_engine)
{
    root_->render(shader, rendering_engine);
}

void Game::set_root(std::shared_ptr<GameObject> gameobject)
{
    root_ = gameobject;
}

std::shared_ptr<GameObject> Game::root() const
{
    return root_;
}

} // namespace SGE

int main(int argc, char** argv)
{
    auto game = SGE::CreateGame(argc, argv);
    game->run();
}
