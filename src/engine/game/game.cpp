#include "camera.h"
#include "game.h"
#include "input.h"
#include "shader.h"
#include "renderingengine.h"

#include <memory>

void SGE::Game::Game::input(const Input& input)
{
    root_->input(input);
}

void SGE::Game::Game::render(Shader& shader, const SGE::RenderingEngine& rendering_engine)
{
    root_->render(shader, rendering_engine);
}

void SGE::Game::Game::update(const float delta)
{
    root_->update(delta);
}

void SGE::Game::Game::fixed_update()
{
    root_->fixed_update();
}

std::shared_ptr<SGE::GameObject> SGE::Game::Game::root()
{
    return root_;
}

void SGE::Game::Game::set_root(std::shared_ptr<SGE::GameObject> gameobject)
{
    root_ = gameobject;
}
