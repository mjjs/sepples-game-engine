#include "basicshader.h"
#include "bitmap.h"
#include "camera.h"
#include "colour.h"
#include "game.h"
#include "material.h"
#include "resourceloader.h"
#include "texture.h"
#include "transform.h"
#include "vertex.h"
#include "vector2.h"
#include "vector3.h"

#include <assimp/material.h>
#include <cstddef>
#include <vector>
#include <iostream>
#include <SDL2/SDL_keycode.h>

Game::Game::Game() :
    level_{"res/levels/testlevel.png", "res/textures/WolfCollection.png"},
    player_{Math::Vector3{0.0F, 0.4375F, 0.0F}}
{
    level_.transform().set_camera(player_.camera());
}

void Game::Game::update()
{
}


void Game::Game::render()
{
    level_.render();
}

void Game::Game::input(const Input& inputs)
{
    player_.input(inputs);
    level_.input(inputs);
}
