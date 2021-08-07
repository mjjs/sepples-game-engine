#ifndef _SGE_GAME_H
#define _SGE_GAME_H

#include "engine/core/input.h"
#include "engine/rendering/camera.h"
#include "engine/rendering/renderingengine.h"
#include "engine/rendering/shader.h"
#include "engine/rendering/window.h"

#include <memory>

int main(int argc, char** argv);

namespace SGE
{

class WindowCloseEvent;
class WindowResizeEvent;

class Game
{
  private:
    // NOLINTNEXTLINE(cppcoreguidelines-avoid-non-const-global-variables)
    static Game* instance_;

    std::unique_ptr<Window> window_;
    bool running_ = true;

    void run();

    void handle_event(Event& event);
    bool handle_window_close(WindowCloseEvent& event);
    bool handle_window_resize(WindowResizeEvent& event);

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
};

std::unique_ptr<Game> CreateGame(int argc, char** argv);

} // namespace SGE

#endif
