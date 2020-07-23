#include "bitmap.h"
#include "colour.h"
#include "gemath.h"
#include "input.h"
#include "level.h"
#include "material.h"
#include "mesh.h"
#include "resourceloader.h"
#include "texture.h"
#include "vector2.h"
#include "vector3.h"
#include "vertex.h"

#include <assimp/material.h>
#include <stdexcept>
#include <string>
#include <vector>

#include <iostream>

Game::Level::Level(const std::string& level_path, const std::string& texture_path) :
    map_{level_path}
{
    Texture texture;
    std::string filename = texture_path.substr(texture_path.find_last_of('/')+1);
    std::string texture_directory = texture_path.substr(0, texture_path.find_last_of('/'));
    texture.id = load_texture(filename, texture_directory);
    texture.path = texture_directory;
    texture.type = aiTextureType_DIFFUSE;

    Material material{};
    material.set_textures(std::vector<Texture>{texture});

    generate_map(material);

    transform_.set_projection(70, 1280, 720, 0.01F, 1000.0F);
}

void Game::Level::render()
{
    shader_.bind();
    shader_.set_transformations(transform_.get_transformation(), transform_.get_projected_transformation());
    mesh_.draw(shader_);
}

void Game::Level::input(const Input& inputs)
{
}

void Game::Level::add_face(std::vector<int>& indices, int start, bool flip) const
{
    if (flip) {
        indices.push_back(start + 2);
        indices.push_back(start + 1);
        indices.push_back(start + 0);
        indices.push_back(start + 3);
        indices.push_back(start + 2);
        indices.push_back(start + 0);
    } else {
        indices.push_back(start + 0);
        indices.push_back(start + 1);
        indices.push_back(start + 2);
        indices.push_back(start + 0);
        indices.push_back(start + 2);
        indices.push_back(start + 3);
    }
}

void Game::Level::add_vertices(std::vector<Vertex>& vertices, int i, int j,
        bool x, bool y, bool z, float offset, const std::vector<float>& texture_coordinates) const
{
    float x_higher = texture_coordinates[0];
    float x_lower = texture_coordinates[1];
    float y_higher = texture_coordinates[2];
    float y_lower = texture_coordinates[3];

    if (x && z) {
        vertices.push_back(Vertex{Math::Vector3{i*SPOT_WIDTH_, offset * SPOT_WIDTH_, j*SPOT_LENGTH_}, Math::Vector3{0,0}, Math::Vector2{x_lower,y_lower}});
        vertices.push_back(Vertex{Math::Vector3{(i+1)*SPOT_WIDTH_, offset * SPOT_WIDTH_, j*SPOT_LENGTH_}, Math::Vector3{0,0}, Math::Vector2{x_higher,y_lower}});
        vertices.push_back(Vertex{Math::Vector3{(i+1)*SPOT_WIDTH_, offset * SPOT_WIDTH_, (j+1)*SPOT_LENGTH_}, Math::Vector3{0,0}, Math::Vector2{x_higher,y_higher}});
        vertices.push_back(Vertex{Math::Vector3{i*SPOT_WIDTH_, offset * SPOT_WIDTH_, (j+1)*SPOT_LENGTH_}, Math::Vector3{0,0}, Math::Vector2{x_lower,y_higher}});
    } else if (y && z) {
        vertices.push_back(Vertex{Math::Vector3{offset * SPOT_WIDTH_, i * SPOT_HEIGHT_, j*SPOT_LENGTH_}, Math::Vector3{0,0}, Math::Vector2{x_lower,y_lower}});
        vertices.push_back(Vertex{Math::Vector3{offset * SPOT_WIDTH_, i * SPOT_HEIGHT_, (j+1)*SPOT_LENGTH_}, Math::Vector3{0,0}, Math::Vector2{x_higher,y_lower}});
        vertices.push_back(Vertex{Math::Vector3{offset * SPOT_WIDTH_, (i + 1) * SPOT_HEIGHT_,(j+1)*SPOT_LENGTH_}, Math::Vector3{0,0}, Math::Vector2{x_higher,y_higher}});
        vertices.push_back(Vertex{Math::Vector3{offset * SPOT_WIDTH_, (i + 1) * SPOT_HEIGHT_,j*SPOT_LENGTH_}, Math::Vector3{0,0}, Math::Vector2{x_lower,y_higher}});
    } else if (x && y) {
        vertices.push_back(Vertex{Math::Vector3{i*SPOT_WIDTH_, j * SPOT_HEIGHT_, offset * SPOT_LENGTH_}, Math::Vector3{0,0}, Math::Vector2{x_lower,y_lower}});
        vertices.push_back(Vertex{Math::Vector3{(i+1)*SPOT_WIDTH_, j * SPOT_HEIGHT_, offset * SPOT_LENGTH_}, Math::Vector3{0,0}, Math::Vector2{x_higher,y_lower}});
        vertices.push_back(Vertex{Math::Vector3{(i+1)*SPOT_WIDTH_, (j + 1) * SPOT_HEIGHT_, offset * SPOT_LENGTH_}, Math::Vector3{0,0}, Math::Vector2{x_higher,y_higher}});
        vertices.push_back(Vertex{Math::Vector3{i*SPOT_WIDTH_, (j + 1) * SPOT_HEIGHT_, offset * SPOT_LENGTH_}, Math::Vector3{0,0}, Math::Vector2{x_lower,y_higher}});
    } else{
        throw std::runtime_error("Invalid plane in level generator");
    }
}

std::vector<float> Game::Level::calculate_texture_coordinates(int colour) const
{
    int texture_x = colour / NUM_TEXTURES_;
    int texture_y = texture_x % NUM_TEX_EXP_;
    texture_x /= NUM_TEX_EXP_;

    std::vector<int> result{
    };

    float x_higher = 1.0F - static_cast<float>(texture_x)/static_cast<float>(NUM_TEX_EXP_);
    float x_lower = x_higher - 1.0F / static_cast<float>(NUM_TEX_EXP_);
    float y_lower = 1.0F - static_cast<float>(texture_y)/static_cast<float>(NUM_TEX_EXP_);
    float y_higher = y_lower - 1.0F / static_cast<float>(NUM_TEX_EXP_);

    return std::vector<float>{x_higher, x_lower, y_higher, y_lower};
}

void Game::Level::generate_map(const Material& material)
{
    std::vector<Vertex> vertices{};
    std::vector<int> indices{};

    for (int i = 0; i < map_.width(); ++i) {
        for (int j = 0; j < map_.height(); ++j) {
            Colour pixel = map_.get_pixel(i, j);
            if (pixel.r == 0 && pixel.g == 0 && pixel.b == 0) {
                continue;
            }

            std::vector<float> texture_coordinates = calculate_texture_coordinates(pixel.g);

            // Floor
            add_face(indices, vertices.size(), true);
            add_vertices(vertices, i, j, true, false, true, 0, texture_coordinates);

            // Ceiling
            add_face(indices, vertices.size(), false);
            add_vertices(vertices, i, j, true, false, true, SPOT_HEIGHT_, texture_coordinates);

            // Walls
            texture_coordinates = calculate_texture_coordinates(pixel.r);

            if (Colour neighbour = map_.get_pixel(i, j-1); neighbour.r == 0 && neighbour.g == 0 && neighbour.b == 0) {
                add_face(indices, vertices.size(), false);
                add_vertices(vertices, i, 0, true, true, false, j, texture_coordinates);
            }

            if (Colour neighbour = map_.get_pixel(i, j+1); neighbour.r == 0 && neighbour.g == 0 && neighbour.b == 0) {
                add_face(indices, vertices.size(), true);
                add_vertices(vertices, i, 0, true, true, false, j + 1, texture_coordinates);
            }

            if (Colour neighbour = map_.get_pixel(i-1, j); neighbour.r == 0 && neighbour.g == 0 && neighbour.b == 0) {
                add_face(indices, vertices.size(), true);
                add_vertices(vertices, 0, j, false, true, true, i, texture_coordinates);
            }

            if (Colour neighbour = map_.get_pixel(i+1, j); neighbour.r == 0 && neighbour.g == 0 && neighbour.b == 0) {
                add_face(indices, vertices.size(), false);
                add_vertices(vertices, 0, j, false, true, true, i + 1, texture_coordinates);
            }
        }
    }

    mesh_ = Mesh(vertices, indices, material);
}

Math::Transform& Game::Level::transform()
{
    return transform_;
}

Math::Vector3 Game::Level::check_collision(const Math::Vector3& old_position, const Math::Vector3& new_position,
        const float width, const float length) const
{
    Math::Vector2 collision_vector{1.0F, 1.0F};
    Math::Vector3 movement_vector = new_position - old_position;

    if (Math::length(movement_vector) > 0) {

        Math::Vector2 block_size{SPOT_WIDTH_, SPOT_LENGTH_};
        Math::Vector2 object_size{width, length};

        Math::Vector2 old_position_2{old_position.x, old_position.z};
        Math::Vector2 new_position_2{new_position.x, new_position.z};

        for (int i = 0; i < map_.height(); ++i) {
            for (int j = 0; j < map_.width(); ++j) {
                if (Colour c = map_.get_pixel(i, j); c.r == 0 && c.g == 0 && c.b == 0) {
                    collision_vector = collision_vector * rectangle_collide(
                            old_position_2,
                            new_position_2,
                            object_size,
                            block_size,
                            block_size * Math::Vector2{static_cast<float>(i),static_cast<float>(j)}
                            );
                }
            }
        }
    }

    return Math::Vector3{collision_vector.x, 0, collision_vector.y};
}

Math::Vector2 Game::Level::rectangle_collide(const Math::Vector2& old_position, const Math::Vector2& new_position,
        const Math::Vector2& size1, const Math::Vector2& size2, const Math::Vector2& pos2) const
{
    Math::Vector2 result{0.0F, 0.0F};

    if (new_position.x + size1.x < pos2.x ||
            new_position.x - size1.x > pos2.x + size2.x * size2.x ||
            old_position.y + size1.y < pos2.y ||
            old_position.y - size1.y > pos2.y + size2.y * size2.y) {
        result.x = 1;
    }

    if (old_position.x + size1.x < pos2.x ||
            old_position.x - size1.x > pos2.x + size2.x * size2.x ||
            new_position.y + size1.y < pos2.y ||
            new_position.y - size1.y > pos2.y + size2.y * size2.y) {
        result.y = 1;
    }

    return result;
}
