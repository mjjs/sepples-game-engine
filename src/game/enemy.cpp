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

void Game::Enemy::idle()
{
}

void Game::Enemy::chase()
{
}

void Game::Enemy::attack()
{
}

void Game::Enemy::dying()
{
}

void Game::Enemy::dead()
{
}

void Game::Enemy::face_camera()
{
    Math::Vector3 direction_to_camera = transform_.translation() - Game::Player::camera_->get_position();
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
    // Ebin
    Math::Vector3 translation = transform_.translation();
    translation.y = -0.01F;
    transform_.set_translation(translation);

    face_camera();

    switch (state_) {
        case EnemyState::IDLE:
            idle();
            break;
        case EnemyState::CHASE:
            chase();
            break;
        case EnemyState::ATTACK:
            attack();
            break;
        case EnemyState::DYING:
            dying();
            break;
        case EnemyState::DEAD:
            dead();
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
