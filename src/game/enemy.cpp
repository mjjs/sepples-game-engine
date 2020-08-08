#include "basicshader.h"
#include "enemy.h"
#include "gemath.h"
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
#include <cassert>
#include <cmath>
#include <vector>

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
}

void Game::Enemy::idle(const Math::Vector3& orientation, float distance_to_camera)
{
}

void Game::Enemy::chase(const Math::Vector3& orientation, float distance_to_camera)
{
    if (distance_to_camera > MOVE_STOP_DISTANCE) {
        // TODO: ADD COLLISION CHECK
        Math::Vector3 old_position = transform_.translation();
        Math::Vector3 new_position = transform_.translation() + (MOVE_SPEED * (-1 * orientation));

        transform_.set_translation(new_position);
    }
}

void Game::Enemy::attack(const Math::Vector3& orientation, float distance_to_camera)
{
}

void Game::Enemy::dying(const Math::Vector3& orientation, float distance_to_camera)
{
}

void Game::Enemy::dead(const Math::Vector3& orientation, float distance_to_camera)
{
}

void Game::Enemy::face_camera(const Math::Vector3& direction_to_camera)
{
    float angle_to_face_camera = Math::to_degrees(std::atan(direction_to_camera.z / direction_to_camera.x));

    if (direction_to_camera.x > 0) {
        angle_to_face_camera += 180;
    }

    Math::Vector3 rotation = transform_.rotation();
    rotation.y = angle_to_face_camera + 90;
    transform_.set_rotation(rotation);
}

void Game::Enemy::update()
{
    Math::Vector3 direction_to_camera = transform_.translation() - Game::Player::camera_->get_position();
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
