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
    model_{"res/models/backpack.obj"}
{
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
    shader_.set_transformations(
            transformer_.get_transformation(),
            transformer_.get_projected_transformation()
            );
    shader_.set_ambient_light_strength(Math::Vector3{0.2F, 0.2F, 0.2F});
    shader_.set_diffuse_light_position(Math::Vector3{1.0F, 1.0F, 1.0F});
    shader_.set_view_position(transformer_.get_camera().get_position());

    model_.draw(shader_);
}

void Game::Game::input(const Input& inputs)
{
    Camera *camera = &transformer_.get_camera();

    float move_speed = .025;

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
