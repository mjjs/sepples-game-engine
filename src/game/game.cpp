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

Bitmap test_level{"res/levels/testlevel.png"};
Texture texture;
Math::Transform transform;

Mesh mesh;

constexpr float SPOT_WIDTH = 1;
constexpr float SPOT_LENGTH = 1;
constexpr float SPOT_HEIGHT = 1;

constexpr int NUM_TEX_EXP = 4;
constexpr int NUM_TEXTURES = NUM_TEX_EXP * NUM_TEX_EXP;

Game::Game::Game()
{
    texture.id = load_texture("WolfCollection.png", "res/textures");
    texture.path = "res/textures";
    texture.type = aiTextureType_DIFFUSE;

    Material material{};
    material.set_textures(std::vector<Texture>{texture});

    std::vector<Vertex> vertices{};
    std::vector<int> indices{};

    for (int i = 0; i < test_level.width(); ++i) {
        for (int j = 0; j < test_level.height(); ++j) {
            Colour pixel = test_level.get_pixel(i, j);
            if (pixel.r == 0 && pixel.g == 0 && pixel.b == 0) {
                continue;
            }

            int texture_x = pixel.g / NUM_TEXTURES;
            int texture_y = texture_x % NUM_TEX_EXP;
            texture_x /= NUM_TEX_EXP;

            float x_higher = 1.0F - static_cast<float>(texture_x)/static_cast<float>(NUM_TEX_EXP);
            float x_lower = x_higher - 1.0F / static_cast<float>(NUM_TEX_EXP);
            float y_lower = 1.0F - static_cast<float>(texture_y)/static_cast<float>(NUM_TEX_EXP);
            float y_higher = y_lower - 1.0F / static_cast<float>(NUM_TEX_EXP);

            // Floor
            indices.push_back(vertices.size() + 2);
            indices.push_back(vertices.size() + 1);
            indices.push_back(vertices.size() + 0);

            indices.push_back(vertices.size() + 3);
            indices.push_back(vertices.size() + 2);
            indices.push_back(vertices.size() + 0);

            vertices.push_back(Vertex{Math::Vector3{i*SPOT_WIDTH,0,j*SPOT_LENGTH}, Math::Vector3{0,0}, Math::Vector2{x_lower,y_lower}});
            vertices.push_back(Vertex{Math::Vector3{(i+1)*SPOT_WIDTH,0,j*SPOT_LENGTH}, Math::Vector3{0,0}, Math::Vector2{x_higher,y_lower}});
            vertices.push_back(Vertex{Math::Vector3{(i+1)*SPOT_WIDTH,0,(j+1)*SPOT_LENGTH}, Math::Vector3{0,0}, Math::Vector2{x_higher,y_higher}});
            vertices.push_back(Vertex{Math::Vector3{i*SPOT_WIDTH,0,(j+1)*SPOT_LENGTH}, Math::Vector3{0,0}, Math::Vector2{x_lower,y_higher}});

            // Ceiling
            indices.push_back(vertices.size() + 0);
            indices.push_back(vertices.size() + 1);
            indices.push_back(vertices.size() + 2);

            indices.push_back(vertices.size() + 0);
            indices.push_back(vertices.size() + 2);
            indices.push_back(vertices.size() + 3);

            vertices.push_back(Vertex{Math::Vector3{i*SPOT_WIDTH,SPOT_HEIGHT,j*SPOT_LENGTH}, Math::Vector3{0,0}, Math::Vector2{x_lower,y_lower}});
            vertices.push_back(Vertex{Math::Vector3{(i+1)*SPOT_WIDTH,SPOT_HEIGHT,j*SPOT_LENGTH}, Math::Vector3{0,0}, Math::Vector2{x_higher,y_lower}});
            vertices.push_back(Vertex{Math::Vector3{(i+1)*SPOT_WIDTH,SPOT_HEIGHT,(j+1)*SPOT_LENGTH}, Math::Vector3{0,0}, Math::Vector2{x_higher,y_higher}});
            vertices.push_back(Vertex{Math::Vector3{i*SPOT_WIDTH,SPOT_HEIGHT,(j+1)*SPOT_LENGTH}, Math::Vector3{0,0}, Math::Vector2{x_lower,y_higher}});

            texture_x = pixel.r / NUM_TEXTURES;
            texture_y = texture_x % NUM_TEX_EXP;
            texture_x /= NUM_TEX_EXP;

            x_higher = 1.0F - static_cast<float>(texture_x)/static_cast<float>(NUM_TEX_EXP);
            x_lower = x_higher - 1.0F / static_cast<float>(NUM_TEX_EXP);
            y_lower = 1.0F - static_cast<float>(texture_y)/static_cast<float>(NUM_TEX_EXP);
            y_higher = y_lower - 1.0F / static_cast<float>(NUM_TEX_EXP);

            // Walls
            if (Colour neighbour = test_level.get_pixel(i, j-1); neighbour.r == 0 && neighbour.g == 0 && neighbour.b == 0) {
                indices.push_back(vertices.size() + 0);
                indices.push_back(vertices.size() + 1);
                indices.push_back(vertices.size() + 2);

                indices.push_back(vertices.size() + 0);
                indices.push_back(vertices.size() + 2);
                indices.push_back(vertices.size() + 3);

                vertices.push_back(Vertex{Math::Vector3{i*SPOT_WIDTH,0,j*SPOT_LENGTH}, Math::Vector3{0,0}, Math::Vector2{x_lower,y_lower}});
                vertices.push_back(Vertex{Math::Vector3{(i+1)*SPOT_WIDTH,0,j*SPOT_LENGTH}, Math::Vector3{0,0}, Math::Vector2{x_higher,y_lower}});
                vertices.push_back(Vertex{Math::Vector3{(i+1)*SPOT_WIDTH,SPOT_HEIGHT,j*SPOT_LENGTH}, Math::Vector3{0,0}, Math::Vector2{x_higher,y_higher}});
                vertices.push_back(Vertex{Math::Vector3{i*SPOT_WIDTH,SPOT_HEIGHT,j*SPOT_LENGTH}, Math::Vector3{0,0}, Math::Vector2{x_lower,y_higher}});
            }

            if (Colour neighbour = test_level.get_pixel(i, j+1); neighbour.r == 0 && neighbour.g == 0 && neighbour.b == 0) {
                indices.push_back(vertices.size() + 2);
                indices.push_back(vertices.size() + 1);
                indices.push_back(vertices.size() + 0);

                indices.push_back(vertices.size() + 3);
                indices.push_back(vertices.size() + 2);
                indices.push_back(vertices.size() + 0);

                vertices.push_back(Vertex{Math::Vector3{i*SPOT_WIDTH,0,(j+1)*SPOT_LENGTH}, Math::Vector3{0,0}, Math::Vector2{x_lower,y_lower}});
                vertices.push_back(Vertex{Math::Vector3{(i+1)*SPOT_WIDTH,0,(j+1)*SPOT_LENGTH}, Math::Vector3{0,0}, Math::Vector2{x_higher,y_lower}});
                vertices.push_back(Vertex{Math::Vector3{(i+1)*SPOT_WIDTH,SPOT_HEIGHT,(j+1)*SPOT_LENGTH}, Math::Vector3{0,0}, Math::Vector2{x_higher,y_higher}});
                vertices.push_back(Vertex{Math::Vector3{i*SPOT_WIDTH,SPOT_HEIGHT,(j+1)*SPOT_LENGTH}, Math::Vector3{0,0}, Math::Vector2{x_lower,y_higher}});
            }

            if (Colour neighbour = test_level.get_pixel(i-1, j); neighbour.r == 0 && neighbour.g == 0 && neighbour.b == 0) {
                indices.push_back(vertices.size() + 2);
                indices.push_back(vertices.size() + 1);
                indices.push_back(vertices.size() + 0);

                indices.push_back(vertices.size() + 3);
                indices.push_back(vertices.size() + 2);
                indices.push_back(vertices.size() + 0);

                vertices.push_back(Vertex{Math::Vector3{i*SPOT_WIDTH,0,j*SPOT_LENGTH}, Math::Vector3{0,0}, Math::Vector2{x_lower,y_lower}});
                vertices.push_back(Vertex{Math::Vector3{i*SPOT_WIDTH,0,(j+1)*SPOT_LENGTH}, Math::Vector3{0,0}, Math::Vector2{x_higher,y_lower}});
                vertices.push_back(Vertex{Math::Vector3{i*SPOT_WIDTH,SPOT_HEIGHT,(j+1)*SPOT_LENGTH}, Math::Vector3{0,0}, Math::Vector2{x_higher,y_higher}});
                vertices.push_back(Vertex{Math::Vector3{i*SPOT_WIDTH,SPOT_HEIGHT,j*SPOT_LENGTH}, Math::Vector3{0,0}, Math::Vector2{x_lower,y_higher}});
            }

            if (Colour neighbour = test_level.get_pixel(i+1, j); neighbour.r == 0 && neighbour.g == 0 && neighbour.b == 0) {
                indices.push_back(vertices.size() + 0);
                indices.push_back(vertices.size() + 1);
                indices.push_back(vertices.size() + 2);

                indices.push_back(vertices.size() + 0);
                indices.push_back(vertices.size() + 2);
                indices.push_back(vertices.size() + 3);

                vertices.push_back(Vertex{Math::Vector3{(i+1)*SPOT_WIDTH,0,j*SPOT_LENGTH}, Math::Vector3{0,0}, Math::Vector2{x_lower,y_lower}});
                vertices.push_back(Vertex{Math::Vector3{(i+1)*SPOT_WIDTH,0,(j+1)*SPOT_LENGTH}, Math::Vector3{0,0}, Math::Vector2{x_higher,y_lower}});
                vertices.push_back(Vertex{Math::Vector3{(i+1)*SPOT_WIDTH,SPOT_HEIGHT,(j+1)*SPOT_LENGTH}, Math::Vector3{0,0}, Math::Vector2{x_higher,y_higher}});
                vertices.push_back(Vertex{Math::Vector3{(i+1)*SPOT_WIDTH,SPOT_HEIGHT,j*SPOT_LENGTH}, Math::Vector3{0,0}, Math::Vector2{x_lower,y_higher}});
            }
        }
    }

    mesh = Mesh(vertices, indices, material);
    transform.set_projection(70, 1280, 720, 0.01F, 1000.0F);
}

void Game::Game::update()
{
}


void Game::Game::render()
{
    shader_.bind();
    shader_.set_transformations(transform.get_transformation(), transform.get_projected_transformation());
    mesh.draw(shader_);
}

void Game::Game::input(const Input& inputs)
{
    if (inputs.is_key_down(SDLK_s)) {
        transform.get_camera().move(transform.get_camera().get_forward(), -.08);
    }

    if (inputs.is_key_down(SDLK_w)) {
        transform.get_camera().move(transform.get_camera().get_forward(), .08);
    }

    if (inputs.is_key_down(SDLK_DOWN)) {
        transform.get_camera().rotate_x(1);
    }

    if (inputs.is_key_down(SDLK_UP)) {
        transform.get_camera().rotate_x(-1);
    }

    if (inputs.is_key_down(SDLK_LEFT)) {
        transform.get_camera().rotate_y(-1);
    }

    if (inputs.is_key_down(SDLK_RIGHT)) {
        transform.get_camera().rotate_y(1);
    }
}
