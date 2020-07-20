#include "camera.h"
#include "directionallight.h"
#include "game.h"
#include "gemath.h"
#include "input.h"
#include "model.h"
#include "pointlight.h"
#include "resourceloader.h"
#include "shader.h"
#include "spotlight.h"
#include "transform.h"
#include "vector3.h"

#include <SDL2/SDL_keycode.h>
#include <cmath>
#include <vector>

#include <iostream>

bool flashlight_on = false;

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
}

void Game::Game::render()
{
    shader_.bind();
    shader_.set_transformations(
            transformer_.get_transformation(),
            transformer_.get_projected_transformation()
            );

    shader_.set_view_position(transformer_.get_camera().get_position());

    DirectionalLight dl{
        Math::Vector3{1.0F, 1.0F, 1.0F},
            Math::Vector3{.5F, .5F, .5F},
    };

    PointLight pl{
        Math::Vector3{1.7F, 0.2F, 2.0F},
            Math::Vector3{.2F, .2F, .2F},
            1.0F,
            0.09F,
            0.032F
    };

    SpotLight flashlight{
        transformer_.get_camera().get_position(),
            transformer_.get_camera().get_forward(),
            Math::Vector3{1.0F, 1.0F, 1.0F},
            flashlight_on ? 1.0F : 0.0F,
            0.045F,
            0.0075F,
            std::cos(Math::to_radians(2.5F)),
            std::cos(Math::to_radians(15.0f))
    };

    shader_.set_uniform(flashlight);
    shader_.set_uniform(pl);
    shader_.set_uniform(dl);

    model_.draw(shader_);
}

void Game::Game::input(const Input& inputs)
{
    Camera *camera = &transformer_.get_camera();

    float move_speed = .025;

    if (inputs.is_key_down(SDLK_d)) {
        camera->move(camera->get_right(), move_speed);
    }

    if (inputs.is_key_just_pressed(SDLK_f)) {
        flashlight_on = !flashlight_on;
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
