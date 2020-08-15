#include "basicshader.h"
#include "enemy.h"
#include "gemath.h"
#include "level.h"
#include "material.h"
#include "mesh.h"
#include "player.h"
#include "resourceloader.h"
#include "texture.h"
#include "transform.h"
#include "vector2.h"
#include "vector3.h"
#include "vertex.h"

#include <assimp/material.h>
#include <chrono>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <memory>
#include <vector>

#include <iostream>

Game::Enemy::Enemy(const Math::Transform& transform) :
    transform_{transform}
{
    Texture texture{};
    texture.id = load_texture("SSWVA1.png", "res/textures");
    texture.path = "res/textures";
    texture.type = aiTextureType_DIFFUSE;

    Material material{};
    material.set_textures(std::vector<Texture>{texture});
    material_ = material;

    if (!mesh_created_) {
        // Create it
        std::vector<Vertex> vertices{
            Vertex{Math::Vector3{-SIZE_X, START, START}, Math::Vector3{0.0F, 0.0F, 0.0F}, Math::Vector2{TEXTURE_MAX_X, TEXTURE_MAX_Y}},
            Vertex{Math::Vector3{-SIZE_X, SIZE_Y, START}, Math::Vector3{0.0F, 0.0F, 0.0F}, Math::Vector2{TEXTURE_MAX_X, TEXTURE_MIN_Y}},
            Vertex{Math::Vector3{SIZE_X, SIZE_Y, START}, Math::Vector3{0.0F, 0.0F, 0.0F}, Math::Vector2{TEXTURE_MIN_X, TEXTURE_MIN_Y}},
            Vertex{Math::Vector3{SIZE_X, START, START}, Math::Vector3{0.0F, 0.0F, 0.0F}, Math::Vector2{TEXTURE_MIN_X, TEXTURE_MAX_Y}},
        };

        std::vector<int> indices{0, 1, 2,
            0, 2, 3,
            };

        mesh_ = Mesh(vertices, indices, material_);

        mesh_created_ = true;
    }

    std::srand(std::time(nullptr));
    last_attack_ = std::chrono::steady_clock::now();
}

void Game::Enemy::idle(const Math::Vector3& orientation, float distance_to_camera)
{
    auto now = std::chrono::steady_clock::now();
    float time_since_last_look = static_cast<float>(std::chrono::duration_cast<std::chrono::milliseconds>(now - last_player_check_).count());

    if (time_since_last_look > 400.0F) {
        Math::Vector2 line_start{transform_.translation().x, transform_.translation().z};
        Math::Vector2 cast_direction{orientation.x, orientation.z};
        Math::Vector2 line_end = line_start + Game::Enemy::SHOOT_DISTANCE * cast_direction;

        bool hit = false;
        bool hit_player = false;

        Math::Vector2 collision_vector = level_->check_intersection(line_start, line_end, hit, false);
        Math::Vector2 player_intersection = level_->line_intersect_rectangle(line_start, line_end,
                Math::Vector2{transform_.get_camera()->get_position().x, transform_.get_camera()->get_position().z},
                Math::Vector2{0.2F, 0.2F}, hit_player); // 0.2F = player size, too lazy to refactor code

        if (hit && hit_player && Math::length(player_intersection - line_start) < Math::length(collision_vector - line_start)) {
            std::cout << "Enemy sees the player\n";
            state_ = EnemyState::CHASE;
        }
    }
}

void Game::Enemy::chase(const Math::Vector3& orientation, float distance_to_camera)
{
    float shoot_threshold = static_cast<float> (std::rand()) / static_cast<float> (RAND_MAX);
    if (shoot_threshold < 0.008F) {
        state_ = EnemyState::ATTACK;
    }

    if (distance_to_camera > MOVE_STOP_DISTANCE) {
        Math::Vector3 old_position = transform_.translation();
        Math::Vector3 new_position = transform_.translation() + (MOVE_SPEED * orientation);

        Math::Vector3 collision_vector = level_->check_collision(
                old_position,
                new_position,
                WIDTH,
                LENGTH
                );

        Math::Vector3 movement_vector = collision_vector * orientation;

        if (Math::length(movement_vector - orientation) != 0) {
            level_->open_doors(new_position);
        }

        if (Math::length(movement_vector) > 0) {
            transform_.set_translation(old_position + MOVE_SPEED * movement_vector);
        }
    } else {
        state_ = EnemyState::ATTACK;
    }
}

void Game::Enemy::attack(const Math::Vector3& orientation, float distance_to_camera)
{
    auto now = std::chrono::steady_clock::now();
    float time_since_last_attack = static_cast<float>(std::chrono::duration_cast<std::chrono::milliseconds>(now - last_attack_).count());

    if (time_since_last_attack > 400.0F) {
        float random_rotate = (static_cast<float> (std::rand()) / static_cast<float> (RAND_MAX) - 0.5F) * 10.0F;
        Math::Vector2 line_start{transform_.translation().x, transform_.translation().z};
        Math::Vector2 cast_direction = Math::rotate(Math::Vector2{orientation.x, orientation.z}, random_rotate);
        Math::Vector2 line_end = line_start + Game::Enemy::SHOOT_DISTANCE * cast_direction;

        bool hit = false;

        bool hit_player = false;

        Math::Vector2 collision_vector = level_->check_intersection(line_start, line_end, hit, false);
        Math::Vector2 player_intersection = level_->line_intersect_rectangle(line_start, line_end,
                Math::Vector2{transform_.get_camera()->get_position().x, transform_.get_camera()->get_position().z},
                Math::Vector2{0.2F, 0.2F}, hit_player); // 0.2F = player size, too lazy to refactor code

        if (hit && hit_player && Math::length(player_intersection - line_start) < Math::length(collision_vector - line_start)) {
            level_->damage_player(15);
            std::cout << "Hit the player\n";
        }

        if (!hit) {
            std::cout << "Missed everything\n";
        } else {
            std::cout << "Hit a wall!\n";
        }
        state_ = EnemyState::CHASE;
        last_attack_ = std::chrono::steady_clock::now();
    }
}

void Game::Enemy::dying(const Math::Vector3& orientation, float distance_to_camera)
{
    state_ = EnemyState::DEAD;
}

void Game::Enemy::dead(const Math::Vector3& orientation, float distance_to_camera)
{
    //std::cout << "Enemy is dead\n";
}

void Game::Enemy::face_camera(const Math::Vector3& direction_to_camera)
{
    float angle_to_face_camera = Math::to_degrees(std::atan(direction_to_camera.z / direction_to_camera.x));

    if (direction_to_camera.x < 0) {
        angle_to_face_camera += 180;
    }

    Math::Vector3 rotation = transform_.rotation();
    rotation.y = angle_to_face_camera + 90;
    transform_.set_rotation(rotation);
}

void Game::Enemy::update()
{
    Math::Vector3 direction_to_camera = Game::Player::camera_->get_position() - transform_.translation();
    Math::Vector3 orientation = Math::normalize(direction_to_camera);
    float distance = Math::length(direction_to_camera);

    // Ebin
    Math::Vector3 translation = transform_.translation();
    translation.y = -0.01F;
    transform_.set_translation(translation);

    face_camera(orientation);

    switch (state_) {
        case EnemyState::IDLE:
            idle(orientation, distance);
            break;
        case EnemyState::CHASE:
            chase(orientation, distance);
            break;
        case EnemyState::ATTACK:
            attack(orientation, distance);
            break;
        case EnemyState::DYING:
            dying(orientation, distance);
            break;
        case EnemyState::DEAD:
            dead(orientation, distance);
            break;

        default:
            break;
    }
}

void Game::Enemy::render(BasicShader& shader)
{
    shader.set_material(material_);
    shader.set_transformations(transform_.get_transformation(), transform_.get_projected_transformation());
    mesh_.draw(shader);
}

void Game::Enemy::set_level(std::shared_ptr<Level> level)
{
    level_ = level;
}

void Game::Enemy::damage(const int amount)
{
    health_ -= amount;

    if (health_ <= 0) {
        state_ = EnemyState::DYING;
    } else if (state_ == EnemyState::IDLE) {
        state_ = EnemyState::CHASE;
    }
}

Math::Vector2 Game::Enemy::size() const
{
    return Math::Vector2{WIDTH, LENGTH};
}

Math::Transform& Game::Enemy::transform()
{
    return transform_;
}
