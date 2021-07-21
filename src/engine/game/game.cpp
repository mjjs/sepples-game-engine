#include "camera.h"
#include "game.h"
#include "input.h"
#include "shader.h"
#include "renderingengine.h"

#include <memory>

namespace SGE {

void Game::Game::render(Shader& shader, const RenderingEngine& rendering_engine)
{
    root_->render(shader, rendering_engine);
}

void Game::Game::update(const float delta)
{
    root_->update(delta);
}

void Game::Game::fixed_update()
{
    root_->fixed_update();
}

std::shared_ptr<GameObject> Game::Game::root()
{
    return root_;
}

void Game::Game::set_root(std::shared_ptr<GameObject> gameobject)
{
    root_ = gameobject;
}

} // namespace SGE
