#include "game.h"
#include "model.h"
#include "resourceloader.h"
#include "shader.h"
#include "transform.h"
#include "vector3.h"

#include <cmath>
#include <vector>

Game::Game::Game() :
    shader_{"basic_vertex.glsl", "basic_fragment.glsl"},
    model_{"res/models/backpack.obj"}
{
    shader_.add_uniform("transform");

    transformer_.set_projection(70, 800, 600, .1, 1000);
    transformer_.set_camera(camera_);
}

void Game::Game::update()
{
    ++temp_;
    transformer_.set_translation({0, 0, 5});
    transformer_.set_rotation({temp_, temp_, -temp_});
    // transformer_.set_scale({.5, .5, .5});

    //transformer_.get_camera().rotate_x(temp_);
    //transformer_.get_camera().move(transformer_.get_camera().get_up(), 0.1);
}

void Game::Game::render()
{
    shader_.bind();
    shader_.set_uniform("transform", transformer_.get_projected_transformation());

    model_.draw(shader_);
}
