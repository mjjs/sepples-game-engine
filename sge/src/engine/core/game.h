#ifndef _SGE_GAME_H
#define _SGE_GAME_H

#include "engine/event/windowminimizeevent.h"
#include "engine/event/windowrestoreevent.h"
#include "engine/imgui/imguirenderer.h"
#include "engine/rendering/window.h"

#include <memory>

int main(int argc, char** argv);

namespace SGE
{

class WindowCloseEvent;
class WindowResizeEvent;
class Scene;

class Game
{
  private:
    // NOLINTNEXTLINE(cppcoreguidelines-avoid-non-const-global-variables)
    static Game* instance_;

    std::unique_ptr<Scene> active_scene_;
    std::unique_ptr<Window> window_;

    bool running_   = true;
    bool minimized_ = false;

    void run();

    void handle_event(Event& event);
    bool handle_window_close(WindowCloseEvent& event);
    bool handle_window_resize(WindowResizeEvent& event);
    bool handle_window_minimize(WindowMinimizeEvent& event);
    bool handle_window_restore(WindowRestoreEvent& event);

    friend int ::main(int argc, char** argv);

  public:
    Game();
    virtual ~Game() = default;

    Game(const Game&) = delete;
    Game(Game&&)      = delete;
    Game& operator=(const Game&) = delete;
    Game& operator=(Game&&) = delete;

    virtual void update([[maybe_unused]] float delta)
    {
    }

    virtual void fixed_update()
    {
    }

    virtual void render_imgui()
    {
    }

    void set_active_scene(std::unique_ptr<Scene>& scene);
    std::unique_ptr<Scene>& active_scene();

    const Window& window() const
    {
        return *window_;
    }

    static Game& get()
    {
        return *instance_;
    }
};

std::unique_ptr<Game> create_game(int argc, char** argv);

} // namespace SGE

#endif
