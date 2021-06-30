#include "game.h"
#include "input.h"
#include "shader.h"

#include <memory>

void SGE::Game::Game::input(const Input& input)
{
    root_->input(input);
}

void SGE::Game::Game::render(Shader& shader)
{
    root_->render(shader);
}

void SGE::Game::Game::update()
{
    root_->update();
}

std::shared_ptr<SGE::GameObject> SGE::Game::Game::root()
{
    return root_;
}

void SGE::Game::Game::set_root(std::shared_ptr<SGE::GameObject> gameobject)
{
    root_ = gameobject;
}
