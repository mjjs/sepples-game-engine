#include "bitmap.h"
#include "camera.h"
#include "colour.h"
#include "door.h"
#include "enemy.h"
#include "game.h"
#include "gemath.h"
#include "input.h"
#include "level.h"
#include "material.h"
#include "medkit.h"
#include "mesh.h"
#include "player.h"
#include "resourceloader.h"
#include "texture.h"
#include "vector2.h"
#include "vector3.h"
#include "vertex.h"

#include <assimp/material.h>
#include <stdexcept>
#include <string>
#include <vector>

#include <SDL2/SDL_keycode.h>

#include <iostream>

const auto find_nearest_vector = [](const Math::Vector2& a, const Math::Vector2& b, const Math::Vector2& relative) {
    if (Math::length(a-relative) > Math::length(b-relative)) {
        return b;
    }
    return a;
};

Game::Level::Level()
{
    next_level();
}

void Game::Level::render(BasicShader& shader)
{
    shader.bind();
    shader.set_transformations(transform_.get_transformation(), transform_.get_projected_transformation());
    mesh_.draw(shader);

    for (Door& door : doors_) {
        door.render(shader);
    }

    for (auto& enemy : enemies_) {
        enemy.render(shader);
    }

    for (auto& medkit : medkits_) {
        medkit.render(shader);
    }

    player_.render(shader);
}

void Game::Level::update()
{
    player_.update();

    for (Door& door : doors_) {
        door.update();
    }

    for (auto& enemy : enemies_) {
        enemy.update();
    }

    for (auto medkit = medkits_.begin(); medkit != medkits_.end(); ) {
        if (medkit->used()) {
            medkit = medkits_.erase(medkit);
        } else {
            medkit->update();
            ++medkit;
        }
    }
}

void Game::Level::input(const Input& inputs)
{
    player_.input(inputs);
}

void Game::Level::open_doors(const Math::Vector3& position, bool exit_level)
{
    for (Door& door : doors_) {
        if (Math::length(door.transform().translation() - position) < 1.0F) {
            door.open();
        }
    }

    if (exit_level) {
        for (auto& exit_point : exits_) {
            if (Math::length(exit_point - position) < 1.0F) {
                next_level();
            }
        }
    }
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
            if (Colour c = map_.get_pixel(i, j); c.is_black()) {
                continue;
            }

            if (Colour c = map_.get_pixel(i, j); c.b != 0) {
                add_special(c.b, i, j);
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
                collision_position_start_.push_back(Math::Vector2{i * SPOT_WIDTH_, j * SPOT_LENGTH_});
                collision_position_end_.push_back(Math::Vector2{(i+1) * SPOT_WIDTH_, j * SPOT_LENGTH_});

                add_face(indices, vertices.size(), false);
                add_vertices(vertices, i, 0, true, true, false, j, texture_coordinates);
            }

            if (Colour neighbour = map_.get_pixel(i, j+1); neighbour.r == 0 && neighbour.g == 0 && neighbour.b == 0) {
                collision_position_start_.push_back(Math::Vector2{i * SPOT_WIDTH_, (j+1) * SPOT_LENGTH_});
                collision_position_end_.push_back(Math::Vector2{(i+1) * SPOT_WIDTH_, (j+1) * SPOT_LENGTH_});

                add_face(indices, vertices.size(), true);
                add_vertices(vertices, i, 0, true, true, false, j + 1, texture_coordinates);
            }

            if (Colour neighbour = map_.get_pixel(i-1, j); neighbour.r == 0 && neighbour.g == 0 && neighbour.b == 0) {
                collision_position_start_.push_back(Math::Vector2{i * SPOT_WIDTH_, j * SPOT_LENGTH_});
                collision_position_end_.push_back(Math::Vector2{i * SPOT_WIDTH_, (j+1) * SPOT_LENGTH_});

                add_face(indices, vertices.size(), true);
                add_vertices(vertices, 0, j, false, true, true, i, texture_coordinates);
            }

            if (Colour neighbour = map_.get_pixel(i+1, j); neighbour.r == 0 && neighbour.g == 0 && neighbour.b == 0) {
                collision_position_start_.push_back(Math::Vector2{(i+1) * SPOT_WIDTH_, j * SPOT_LENGTH_});
                collision_position_end_.push_back(Math::Vector2{(i+1) * SPOT_WIDTH_, (j+1) * SPOT_LENGTH_});

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

void Game::Level::add_door(int x, int y)
{
    Math::Transform door_transform = transform_;

    bool is_x_axis = map_.get_pixel(x, y-1).is_black() && map_.get_pixel(x, y+1).is_black();
    bool is_y_axis = map_.get_pixel(x-1, y).is_black() && map_.get_pixel(x+1, y).is_black();

    if (!(is_x_axis ^ is_y_axis)) {
        throw std::runtime_error("Invalid door location");
    }

    Math::Vector3 open_position{};

    if (is_y_axis) {
        door_transform.set_translation(Math::Vector3{static_cast<float>(x), 0.0F, y + SPOT_LENGTH_ / 2.0F});
        open_position = door_transform.translation() - Math::Vector3{0.9F, 0.0F, 0.0F};
    } else {
        door_transform.set_translation(Math::Vector3{x + SPOT_WIDTH_ / 2.0F, 0.0F, static_cast<float>(y)});
        door_transform.set_rotation(Math::Vector3{0.0F, 90.0F, 0.0F});

        open_position = door_transform.translation() - Math::Vector3{0.0F, 0.0F, 0.9F};
    }

    doors_.emplace_back(Door{door_transform, material_, open_position});
}

void Game::Level::add_special(int blue_value, int x, int y)
{
    switch (blue_value) {
        case 1:
            player_ = Player{Math::Vector3{(x + 0.5F) * SPOT_WIDTH_, 0.4375F, (y + 0.5F) * SPOT_HEIGHT_}};
            player_.set_level(this);
            break;
        case 16:
            add_door(x, y);
            break;
        case 97: {
                      exits_.push_back(Math::Vector3{(x + 0.5F) * SPOT_WIDTH_, 0.4375F, (y + 0.5F) * SPOT_HEIGHT_});
                      break;
                  }
        case 128: {
                      Math::Transform enemy_transform{};
                      enemy_transform.set_translation(Math::Vector3{(x + 0.5F) * SPOT_WIDTH_, 0.4375F, (y + 0.5F) * SPOT_HEIGHT_});
                      enemy_transform.set_projection(80, 1280, 720, 0.01F, 1000.0F);
                      enemy_transform.set_camera(player_.camera_);
                      Enemy e(enemy_transform);
                      e.set_level(this);
                      enemies_.push_back(e);
                      break;
                  }
        case 192: {
                     Math::Transform medkit_transform{};
                     medkit_transform.set_translation(Math::Vector3{(x + 0.5F) * SPOT_WIDTH_, 0, (y + 0.5F) * SPOT_HEIGHT_});
                     medkit_transform.set_projection(80, 1280, 720, 0.01F, 1000.0F);
                     medkit_transform.set_camera(player_.camera_);
                     medkits_.push_back(Medkit(medkit_transform, &player_));
                     break;
                 }
    }
}

Math::Vector3 Game::Level::check_collision(const Math::Vector3& old_position, const Math::Vector3& new_position,
        const float width, const float length)
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

        for (Door& door : doors_) {
            Math::Vector2 door_size = door.size();

            Math::Vector3 door_pos_3 = door.transform().translation();
            Math::Vector2 door_pos{door_pos_3.x, door_pos_3.z};
            collision_vector = collision_vector * rectangle_collide(
                    old_position_2,
                    new_position_2,
                    object_size,
                    door_size,
                    block_size * door_pos
                    );
        }
    }

    return Math::Vector3{collision_vector.x, 0, collision_vector.y};
}

Math::Vector2 Game::Level::check_intersection(const Math::Vector2& start, const Math::Vector2& end, bool& hit, bool hurt_monsters)
{
    Math::Vector2 nearest_intersection{0.0F, 0.0F};
    hit = false;

    for (size_t i = 0; i < collision_position_start_.size(); ++i) {
        bool collided = false;

        Math::Vector2 collision_vector = line_intersect(start, end,
                collision_position_start_[i], collision_position_end_[i], collided);

        if (!hit) {
            hit = true;
            nearest_intersection = collision_vector;
            continue;
        }

        if (collided) {
            hit = true;
            nearest_intersection = find_nearest_vector(nearest_intersection, collision_vector, start);
        }
    }

    for (Door& door : doors_) {
        Math::Vector2 door_size = door.size();
        Math::Vector3 door_pos_3 = door.transform().translation();
        Math::Vector2 door_pos{door_pos_3.x, door_pos_3.z};
        bool collided = false;
        Math::Vector2 collision_vector = line_intersect_rectangle(start, end, door_pos, door_size, collided);

        if (collided) {
            nearest_intersection = find_nearest_vector(nearest_intersection, collision_vector, start);
        }
    }

    if (hurt_monsters) {
        bool hit_enemy = false;
        Enemy* nearest_enemy;
        Math::Vector2 nearest_enemy_intersection{0.0F, 0.0F};

        for (Enemy& enemy : enemies_) {
            Math::Vector2 enemy_size = enemy.size();
            Math::Vector3 enemy_pos_3 = enemy.transform().translation();
            Math::Vector2 enemy_pos{enemy_pos_3.x, enemy_pos_3.z};
            bool collided = false;
            Math::Vector2 collision_vector = line_intersect_rectangle(start, end, enemy_pos, enemy_size, collided);

            if (collided) {
                nearest_enemy_intersection = find_nearest_vector(nearest_enemy_intersection, collision_vector, start);
                hit_enemy = true;
                if (collision_vector == nearest_enemy_intersection) {
                    nearest_enemy = &enemy;
                }
            }
        }

        if (hit_enemy) {
            std::cout << nearest_enemy_intersection << '\n';
            if (Math::length(nearest_enemy_intersection - start) < Math::length(nearest_intersection - start)) {
                nearest_enemy->damage(Player::DAMAGE);
            }
        }
    }

    return nearest_intersection;
}

Math::Vector2 Game::Level::line_intersect(const Math::Vector2& start_1, const Math::Vector2& end_1,
        const Math::Vector2& start_2, const Math::Vector2& end_2, bool& hit)
{
    const auto cross_product = [&](const Math::Vector2& lhs, const Math::Vector2& rhs){
        return lhs.x * rhs.y - lhs.y * rhs.x;
    };

    Math::Vector2 line_1 = end_1 - start_1;
    Math::Vector2 line_2 = end_2 - start_2;

    float cross = cross_product(line_1, line_2);
    if (cross == 0) {
        hit = false;
        return Math::Vector2{0.0F, 0.0F};
    }

    const Math::Vector2 dist_between_line_starts = start_2 - start_1;

    float a = cross_product(dist_between_line_starts, line_2) / cross;
    float b = cross_product(dist_between_line_starts, line_1) / cross;
    const auto in_range = [&](const float left, const float right, const float value){
        return left <= value && value <= right;
    };

    if (in_range(0.0F, 1.0F, a) && in_range(0.0F, 1.0F, b)) {
        hit = true;
        return start_1 + (a * line_1);
    }

    hit = false;
    return Math::Vector2{0.0F, 0.0F};
}

Math::Vector2 Game::Level::line_intersect_rectangle(const Math::Vector2& line_start, const Math::Vector2& line_end,
        const Math::Vector2& rect_pos, const Math::Vector2& rect_size, bool& hit)
{
    hit = false;
    Math::Vector2 result{0.0F, 0.0F};

    Math::Vector2 collision_vector = line_intersect(line_start, line_end, rect_pos,
            Math::Vector2{rect_pos.x + rect_size.x, rect_pos.y}, hit);
    if (hit) {
        result = find_nearest_vector(result, collision_vector, line_start);
    }

    collision_vector = line_intersect(line_start, line_end, rect_pos,
            Math::Vector2{rect_pos.x, rect_pos.y + rect_size.y}, hit);
    if (hit) {
        result = find_nearest_vector(result, collision_vector, line_start);
    }

    collision_vector = line_intersect(line_start, line_end, Math::Vector2{rect_pos.x, rect_pos.y+rect_size.y},
           rect_pos + rect_size, hit);
    if (hit) {
        result = find_nearest_vector(result, collision_vector, line_start);
    }

    collision_vector = line_intersect(line_start, line_end, Math::Vector2{rect_pos.x + rect_size.x, rect_pos.y},
            rect_pos + rect_size, hit);
    if (hit) {
        result = find_nearest_vector(result, collision_vector, line_start);
    }

    return result;
}

Math::Vector2 Game::Level::rectangle_collide(const Math::Vector2& old_position, const Math::Vector2& new_position,
        const Math::Vector2& size1, const Math::Vector2& size2, const Math::Vector2& pos2)
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

std::vector<Game::Enemy>& Game::Level::enemies()
{
    return enemies_;
}

void Game::Level::damage_player(const int amount)
{
    player_.damage(amount);
}

Game::Player& Game::Level::player()
{
    return player_;
}

void Game::Level::next_level()
{
    ++current_level_;
    Bitmap map("res/levels/level" + std::to_string(current_level_) + ".png");
    map_ = map;

    transform_.set_camera(Player::camera_);
    transform_.set_projection(80, 1280, 720, 0.01F, 1000.0F);

    Texture texture;
    std::string filename = "WolfCollection.png";
    std::string texture_directory = "res/textures";
    texture.id = load_texture(filename, texture_directory);
    texture.path = texture_directory;
    texture.type = aiTextureType_DIFFUSE;

    Material material{};
    material.set_textures(std::vector<Texture>{texture});
    material_ = material;

    generate_map(material);
}
