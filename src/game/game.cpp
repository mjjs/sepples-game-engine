#include "game.h"
#include "mesh.h"
#include "resourceloader.h"
#include "shader.h"
#include "transform.h"
#include "vector3.h"

#include <cmath>
#include <vector>

Game::Game::Game()
{
    const std::vector<Math::Vector3> pyramid{
        {-1.0, -1.0, 0.0},
            {0.0, 1.0, 0.0},
            {1.0, -1.0, 0.0},
            {0.0, -1.0, 1.0}
    };

    const std::vector<int> indices{
        0,1,3,
            3,1,2,
            2,1,0,
            0,2,3};

    mesh_.set_vertices(pyramid, indices);

    shader_.add_vertex_shader(load_shader("basic_vertex.glsl"));
    shader_.add_fragment_shader(load_shader("basic_fragment.glsl"));
    shader_.compile_shader();
    shader_.add_uniform("transform");
}

void Game::Game::input()
{
}

void Game::Game::update()
{
    ++temp_;
    // transformer_.set_translation({std::sin(temp_), 0, 0});
    transformer_.set_rotation({0, temp_, 0});
    // transformer_.set_scale({asd, asd, asd});
}

void Game::Game::render()
{
    shader_.bind();
    shader_.set_uniform("transform", transformer_.get_transformation());

    mesh_.draw();
}
