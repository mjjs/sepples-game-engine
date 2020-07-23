#include "game.h"
#include "level.h"
#include "vector3.h"

#include <memory>

Game::Game::Game() :
    level_{std::make_shared<Level>("res/levels/testlevel.png", "res/textures/WolfCollection.png")},
    player_{Math::Vector3{8.0F, 0.4375F, 10.0F}}
{
    level_->transform().set_camera(player_.camera());
    player_.set_level(level_);
}

void Game::Game::update()
{
    player_.update();
}


void Game::Game::render()
{
    level_->render();
}

void Game::Game::input(const Input& inputs)
{
    player_.input(inputs);
    level_->input(inputs);
}
