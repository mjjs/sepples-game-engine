#include "game.h"
#include "mesh.h"
#include "resourceloader.h"
#include "shader.h"
#include "transform.h"
#include "vector3.h"

#include <cmath>
#include <vector>

Game::Game::Game() :
    mesh_{load_mesh("box.obj")}
{
    shader_.add_vertex_shader(load_shader("basic_vertex.glsl"));
    shader_.add_fragment_shader(load_shader("basic_fragment.glsl"));
    shader_.compile_shader();
    shader_.add_uniform("transform");

    transformer_.set_projection(70, 800, 600, .1, 1000);
}

void Game::Game::input()
{
}

void Game::Game::update()
{
    ++temp_;
    transformer_.set_translation({0, 0, 5});
    transformer_.set_rotation({temp_, temp_, -temp_});
    // transformer_.set_scale({.5, .5, .5});
}

void Game::Game::render()
{
    shader_.bind();
    shader_.set_uniform("transform", transformer_.get_projected_transformation());

    mesh_.draw();
}
