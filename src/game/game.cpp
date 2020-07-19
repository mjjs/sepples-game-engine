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

    shader_.add_uniform("directional_light.direction");
    shader_.add_uniform("directional_light.colour");

    shader_.add_uniform("point_light.position");
    shader_.add_uniform("point_light.colour");
    shader_.add_uniform("point_light.constant");
    shader_.add_uniform("point_light.linear");
    shader_.add_uniform("point_light.quadratic");

    shader_.add_uniform("spot_light.position");
    shader_.add_uniform("spot_light.direction");
    shader_.add_uniform("spot_light.colour");
    shader_.add_uniform("spot_light.cut_off");
    shader_.add_uniform("spot_light.outer_cut_off");
    shader_.add_uniform("spot_light.constant");
    shader_.add_uniform("spot_light.linear");
    shader_.add_uniform("spot_light.quadratic");
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
    //shader_.set_ambient_light_strength(Math::Vector3{0.2F, 0.2F, 0.2F});
    //shader_.set_diffuse_light_position(Math::Vector3{1.0F, 1.0F, 1.0F});
    shader_.set_view_position(transformer_.get_camera().get_position());

    DirectionalLight dl{
        Math::Vector3{1.0F, 1.0F, 1.0F},
            Math::Vector3{.5F, .5F, .5F},
    };

    shader_.set_uniform("directional_light.direction", dl.direction);
    shader_.set_uniform("directional_light.colour", dl.colour);

    PointLight pl{
        Math::Vector3{1.7F, 0.2F, 2.0F},
            Math::Vector3{.2F, .2F, .2F},
            1.0F,
            0.09F,
            0.032F
    };

    shader_.set_uniform("point_light.position", pl.position);
    shader_.set_uniform("point_light.colour", pl.colour);
    shader_.set_uniform("point_light.constant", pl.constant);
    shader_.set_uniform("point_light.linear", pl.linear);
    shader_.set_uniform("point_light.quadratic", pl.quadratic);

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

    shader_.set_uniform("spot_light.position", flashlight.position);
    shader_.set_uniform("spot_light.direction", flashlight.direction);
    shader_.set_uniform("spot_light.colour", flashlight.colour);
    shader_.set_uniform("spot_light.constant", flashlight.constant);
    shader_.set_uniform("spot_light.linear", flashlight.linear);
    shader_.set_uniform("spot_light.quadratic", flashlight.quadratic);
    shader_.set_uniform("spot_light.cut_off", flashlight.cut_off);
    shader_.set_uniform("spot_light.outer_cut_off", flashlight.outer_cut_off);

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
