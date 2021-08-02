#include "game.h"

namespace SGE {

void Game::update(float delta)
{
    root_->update(delta);
}

void Game::fixed_update()
{
    root_->fixed_update();
}

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
