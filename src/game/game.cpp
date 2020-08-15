#include "enemy.h"
#include "game.h"
#include "level.h"
#include "vector3.h"

#include <memory>

Game::Game::Game() :
    level_{std::make_shared<Level>("res/levels/testlevel.png", "res/textures/WolfCollection.png")}
{
}

void Game::Game::update()
{
    if (level_->player().dead()) {
        game_over();
    }

    if (Game::is_running) {
        level_->update();
    }
}

void Game::Game::render()
{
    if (Game::is_running) {
        level_->render(shader_);
    }
}

void Game::Game::input(const Input& inputs)
{
    level_->input(inputs);
}

void Game::Game::game_over()
{
    Game::Game::is_running = false;
}

void Game::Game::load_next_level()
{
    ++level_number_;
}
