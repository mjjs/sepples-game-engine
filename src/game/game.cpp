#include "camera.h"
#include "directionallight.h"
#include "game.h"
#include "sgemath.h"
#include "input.h"
#include "material.h"
#include "mesh.h"
#include "model.h"
#include "pointlight.h"
#include "resourceloader.h"
#include "shader.h"
#include "spotlight.h"
#include "texture.h"
#include "transform.h"
#include "vector3.h"
#include "vertex.h"

#include <SDL2/SDL_keycode.h>
#include <cmath>
#include <vector>

#include <iostream>

bool flashlight_on = false;
float pl_pos = 1.0F;
float pl_max = 8.0F;
bool ascending = true;

Game::Game::Game() :
    model_{"res/models/backpack.obj"}
{
    transformer_.set_projection(70, 800, 600, .1, 1000);
    transformer_.set_camera(camera_);
}

void Game::Game::update()
{
    if (ascending) {
        if (pl_pos < pl_max) {
            pl_pos += 0.1F;
        } else {
            ascending = false;
        }
    } else {
        if (pl_pos > -pl_max) {
            pl_pos -= 0.1F;
        } else {
            ascending = true;
        }
    }
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

    DirectionalLight dl;
    dl.direction = Math::Vector3{1.0F, 5.0F, 1.0F};
    dl.colour = Math::Vector3{1.0F, 1.0F, 1.0F};
    dl.intensity = 0.7F;

    PointLight pl;
    pl.position = Math::Vector3{0.0F, 1.0F, pl_pos};
    pl.colour = Math::Vector3{0.0F, 0.5F, 1.0F};
    pl.intensity = 0.5F;
    pl.constant = 1.0F;
    pl.linear = 0.09F;
    pl.quadratic = 0.032F;

    SpotLight flashlight;
    flashlight.position = transformer_.get_camera().get_position();
    flashlight.direction = transformer_.get_camera().get_forward();
    flashlight.colour = Math::Vector3{1.0F, 1.0F, 1.0F};
    flashlight.intensity = flashlight_on ? 1.0F : 0.0F;
    flashlight.cut_off = std::cos(Math::to_radians(12.5F));
    flashlight.outer_cut_off = std::cos(Math::to_radians(17.5F));
    flashlight.constant = 1.0F;
    flashlight.linear = 0.09F;
    flashlight.quadratic = 0.032F;

    shader_.set_uniform(flashlight);
    shader_.set_uniform(pl);
    shader_.set_uniform(dl);

    model_.draw(shader_);

    std::vector<Vertex> vertices = {
        {{-10, -2, -10}, {0, 0}, {0, 0}},
        {{-10, -2, 30}, {0, 0}, {0, 1}},
        {{30, -2, -10}, {0, 0}, {1, 0}},
        {{30, -2, 30}, {0, 0}, {1, 1}},
    };

    std::vector<int> indices = {0, 1, 2, 2, 1, 3};
    Material mat{
        std::vector<Texture>{}, {.2,.2,.2}, {.3,1,1}, {1,1,1}
    };
    mat.set_shininess(1);

    Mesh m{vertices, indices,mat };
    m.draw(shader_);
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
