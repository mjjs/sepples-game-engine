#include "camera.h"
#include "game.h"
#include "input.h"
#include "model.h"
#include "resourceloader.h"
#include "shader.h"
#include "transform.h"
#include "vector3.h"

#include <SDL2/SDL_keycode.h>
#include <cmath>
#include <vector>

#include <iostream>

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
    //transformer_.set_rotation({0, temp_, 0});
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

void Game::Game::input(const Input& inputs)
{
    Camera *camera = &transformer_.get_camera();

    float modifier = 1;
    if (inputs.is_key_down(SDLK_LSHIFT)) {
        modifier = .2;
    }

    float move_speed = modifier * 0.1;

    if (inputs.is_key_down(SDLK_d)) {
        camera->move(camera->get_right(), move_speed);
    }

    if (inputs.is_key_down(SDLK_a)) {
        camera->move(camera->get_left(), move_speed);
    }

    if (inputs.is_key_down(SDLK_w)) {
        camera->move(camera->get_forward(), move_speed);
    }

    if (inputs.is_key_down(SDLK_s)) {
        camera->move(camera->get_forward(), -move_speed);
    }

    if (inputs.is_key_down(SDLK_UP)) {
        camera->rotate_x(-1);
    }

    if (inputs.is_key_down(SDLK_DOWN)) {
        camera->rotate_x(1);
    }

    if (inputs.is_key_down(SDLK_LEFT)) {
        camera->rotate_y(-1);
    }

    if (inputs.is_key_down(SDLK_RIGHT)) {
        camera->rotate_y(1);
    }
}
