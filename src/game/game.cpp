#include "enemy.h"
#include "game.h"
#include "level.h"
#include "vector3.h"

#include <memory>

Game::Game::Game() :
    level_{std::make_shared<Level>("res/levels/testlevel.png", "res/textures/WolfCollection.png")},
    player_{Math::Vector3{8.0F, 0.4375F, 10.0F}}
{
    player_.set_level(level_);
    level_->set_player(&player_);
    for (Enemy& enemy : level_->enemies()) {
        enemy.set_level(level_);
    }
}

void Game::Game::update()
{
    if (player_.dead()) {
        game_over();
    }

    if (Game::is_running) {
        player_.update();
        level_->update();
    }
}

void Game::Game::render()
{
    if (Game::is_running) {
        level_->render(shader_);
        player_.render(shader_);
    }
}

void Game::Game::input(const Input& inputs)
{
    player_.input(inputs);
    level_->input(inputs);
}

void Game::Game::game_over()
{
    Game::Game::is_running = false;
}
