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
#include <string>
#include <vector>

#include <iostream>

Game::Enemy::Enemy(const Math::Transform& transform) :
    transform_{transform}
{
    if (!animations_created_) {
        const auto create_material = [&](const std::string& texture_name){
            Texture texture{};
            texture.id = load_texture(texture_name, "res/textures");
            texture.path = "res/textures";
            texture.type = aiTextureType_DIFFUSE;

            Material material{};
            material.set_textures(std::vector<Texture>{texture});
            return material;
        };

        std::vector<Material> materials{
            // Walk
            create_material("SSWVA1.png"),
            create_material("SSWVB1.png"),
            create_material("SSWVC1.png"),
            create_material("SSWVD1.png"),

            // Attack
            create_material("SSWVE0.png"),
            create_material("SSWVF0.png"),
            create_material("SSWVG0.png"),

            // Pain
            create_material("SSWVH0.png"),

            // Dying
            create_material("SSWVI0.png"),
            create_material("SSWVJ0.png"),
            create_material("SSWVK0.png"),
            create_material("SSWVL0.png"),

            // Dead
            create_material("SSWVM0.png"),
        };

        animations_created_ = true;
        animations_ = materials;

    }

    material_ = animations_[1];

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
    last_run_animation_change_ = std::chrono::steady_clock::now();
}

void Game::Enemy::idle(const Math::Vector3& orientation, float distance_to_camera)
{
    material_ = animations_[0];
    auto now = std::chrono::steady_clock::now();
    float time_since_last_look = static_cast<float>(std::chrono::duration_cast<std::chrono::milliseconds>(now - last_player_check_).count());

    if (time_since_last_look > 400.0F) {
        material_ = animations_[1];

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
    auto now = std::chrono::steady_clock::now();
    float time_since_last_anim_change = static_cast<float>(std::chrono::duration_cast<std::chrono::milliseconds>(now - last_run_animation_change_).count());

    if (time_since_last_anim_change > 250) {
        material_ = animations_[last_run_animation_ % 4];
        ++last_run_animation_;
        last_run_animation_change_ = now;
    }

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
            level_->open_doors(new_position, false);
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
    float time_since_last_anim_change = static_cast<float>(std::chrono::duration_cast<std::chrono::milliseconds>(now - last_run_animation_change_).count());

    if (time_since_last_attack < 10.0F) {
        material_ = animations_[4];
    } else if (time_since_last_attack < 350.0F) {
        material_ = animations_[5];
    } if (time_since_last_attack > 400.0F) {
        material_ = animations_[6];

        if (time_since_last_anim_change > 850) {
            material_ = animations_[(last_attack_animation_ % 3)+4];
            ++last_attack_animation_;
            last_attack_animation_change_ = now;
        }

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
        }

        state_ = EnemyState::CHASE;
        last_attack_ = std::chrono::steady_clock::now();

        material_ = animations_[6];
    }
}

void Game::Enemy::dying(const Math::Vector3& orientation, float distance_to_camera)
{
    auto now = std::chrono::steady_clock::now();

    if (!dead_) {
        dead_ = true;
        death_time_ = now;
    }

    float time_since_death = static_cast<float>(std::chrono::duration_cast<std::chrono::milliseconds>(now - death_time_).count());
    if (time_since_death < 100.0F) {
        material_ = animations_[8];
    } else if (time_since_death < 300.0F) {
        material_ = animations_[9];
    } else if (time_since_death < 450.0F) {
        material_ = animations_[10];
    } else if (time_since_death < 600.0F) {
        material_ = animations_[11];
    } else {
        state_ = EnemyState::DEAD;
    }
}

void Game::Enemy::dead(const Math::Vector3& orientation, float distance_to_camera)
{
    material_ = animations_[12];
    //Math::Vector3 translation = transform_.translation();
    //translation.y = 0.01F;
    //transform_.set_translation(translation);
    //transform_.set_rotation(Math::Vector3{90.0F, 0.0F, 0.0F});
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
    if (state_ != EnemyState::DYING && state_ != EnemyState::DEAD) {
        Math::Vector3 translation = transform_.translation();
        translation.y = -0.01F;
        transform_.set_translation(translation);
    }

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
    mesh_.set_material(material_);
    shader.set_material(material_);
    shader.set_transformations(transform_.get_transformation(), transform_.get_projected_transformation());
    mesh_.draw(shader);
}

void Game::Enemy::set_level(Level* level)
{
    level_ = level;
}

void Game::Enemy::damage(const int amount)
{
    health_ -= amount;
    health_ = 0;
    std::cout << "Enemy health left: " << health_ << '\n';

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
