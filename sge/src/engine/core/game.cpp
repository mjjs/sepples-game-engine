#include "engine/core/game.h"

#include "engine/core/input.h"
#include "engine/core/log.h"
#include "engine/core/timer.h"
#include "engine/debug/profiler.h"
#include "engine/ecs/scene.h"
#include "engine/event/event.h"
#include "engine/event/windowcloseevent.h"
#include "engine/event/windowresizeevent.h"
#include "engine/rendering/renderer.h"
#include "engine/rendering/renderer2d.h"
#include "engine/rendering/window.h"

#include <memory>
#include <utility>

namespace SGE
{

Game* Game::instance_ = nullptr; // NOLINT

Game::Game()
{
    instance_ = this;

    window_ = Window::create();
    window_->set_event_callback(BIND_EVENT_FN(Game::handle_event));

    Log::init();
    Renderer::init();
    Renderer2D::init();
}

void Game::run()
{
    SGE_PROFILE_FUNCTION();

    Timer timer{};

    timer.start_timer();
    unsigned int frames_rendered_this_second = 0;

    while (running_) {
        timer.update_times();
        window_->update();

        if (minimized_) {
            continue;
        }

        if (active_scene_) {
            active_scene_->update(timer.fixed_time_step());
        }

        Input::update();

        while (timer.game_needs_updating()) {
            if (active_scene_) {
                active_scene_->fixed_update();
            }

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
    Event::dispatch<WindowCloseEvent>(event,
                                      BIND_EVENT_FN(Game::handle_window_close));

    Event::dispatch<WindowResizeEvent>(
        event, BIND_EVENT_FN(Game::handle_window_resize));
    Event::dispatch<WindowMinimizeEvent>(
        event, BIND_EVENT_FN(Game::handle_window_minimize));
    Event::dispatch<WindowRestoreEvent>(
        event, BIND_EVENT_FN(Game::handle_window_restore));

    if (event.is_in_category(EventCategory::INPUT)) {
        Input::handle_input_event(event);
    }
}

bool Game::handle_window_close([[maybe_unused]] WindowCloseEvent& event)
{
    running_ = false;
    return true;
}

bool Game::handle_window_resize(WindowResizeEvent& event)
{
    auto width  = event.width();
    auto height = event.height();

    Renderer::set_viewport(0, 0, width, height);
    if (active_scene_) {
        active_scene_->on_window_resized(width, height);
    }

    return false;
}

bool Game::handle_window_minimize([[maybe_unused]] WindowMinimizeEvent& event)
{
    minimized_ = true;
    return true;
}

bool Game::handle_window_restore([[maybe_unused]] WindowRestoreEvent& event)
{
    minimized_ = false;
    return true;
}

void Game::set_active_scene(std::unique_ptr<Scene>& scene)
{
    active_scene_ = std::move(scene);
}

std::unique_ptr<Scene>& Game::active_scene()
{
    return active_scene_;
}

} // namespace SGE

int main(int argc, char** argv)
{
    SGE_PROFILER_START("profiler-create-game.json");
    auto game = SGE::CreateGame(argc, argv);
    SGE_PROFILER_STOP();

    SGE_PROFILER_START("profiler-main-loop.json");
    game->run();
    SGE_PROFILER_STOP();
}
