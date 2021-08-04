#ifndef _SGE_GAME_H
#define _SGE_GAME_H

#include "camera.h"
#include "gameobject.h"
#include "input.h"
#include "renderingengine.h"
#include "shader.h"
#include "window.h"

#include <memory>

int main(int argc, char** argv);

namespace SGE
{

class WindowCloseEvent;

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

    friend int ::main(int argc, char** argv);

    // OLD STUFF TO BE REMOVED
    RenderingEngine rendering_engine_;
    std::shared_ptr<GameObject> root_ = std::make_shared<GameObject>();

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

    // OLD API TO BE REMOVED
    virtual void render(Shader& shader,
                        const RenderingEngine& rendering_engine);
    void set_root(std::shared_ptr<GameObject> gameobject);
    std::shared_ptr<GameObject> root() const;
};

std::unique_ptr<Game> CreateGame(int argc, char** argv);

} // namespace SGE

#endif
