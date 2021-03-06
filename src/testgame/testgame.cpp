#include "camera.h"
#include "gamecomponent.h"
#include "input.h"
#include "material.h"
#include "mesh.h"
#include "meshrenderer.h"
#include "model.h"
#include "modelrenderer.h"
#include "testgame.h"
#include "texture.h"
#include "transform.h"
#include "vertex.h"

//#include <SDL2/SDL_keycode.h>
#include <vector>

#include <iostream>

TestGame::TestGame()
{
    Math::Transform transform{};
    Math::Transform::set_projection(70, 800, 600, .1, 1000);
    transform.set_camera(camera_);

    root_.set_transform(transform);

    std::vector<Vertex> vertices = {
        {{-10, -2, -10}, {0, 0}, {0, 0}},
        {{-10, -2, 30}, {0, 0}, {0, 1}},
        {{30, -2, -10}, {0, 0}, {1, 0}},
        {{30, -2, 30}, {0, 0}, {1, 1}},
    };

    std::vector<int> indices = {0, 1, 2, 2, 1, 3};
    Material mat{
        std::vector<Texture>{}, {.2,0,0}, {.3,1,1}, {0,0,0}
    };
    mat.set_shininess(1);

    Mesh m{vertices, indices, mat};

    root_.add_component(std::make_shared<MeshRenderer>(m, mat));
    root_.add_component(std::make_shared<ModelRenderer>(Model("res/models/backpack.obj")));
}

void TestGame::init()
{
}

void TestGame::update()
{
    root_.update();
}

void TestGame::render()
{
    root_.render();
}

void TestGame::input(const Input& inputs)
{
    Camera* camera = &root_.transform().get_camera();

    const float move_speed = .025;

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
