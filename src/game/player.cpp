#include "basicshader.h"
#include "camera.h"
#include "gemath.h"
#include "input.h"
#include "level.h"
#include "material.h"
#include "mesh.h"
#include "player.h"
#include "resourceloader.h"
#include "texture.h"
#include "vector2.h"
#include "vector3.h"

#include <chrono>
#include <cmath>
#include <iostream>

Game::Player::Player()
{
    std::vector<Vertex> vertices{
        Vertex{Math::Vector3{-SIZE_X, START, START}, Math::Vector3{0.0F, 0.0F, 0.0F}, Math::Vector2{TEXTURE_MAX_X, TEXTURE_MAX_Y}},
        Vertex{Math::Vector3{-SIZE_X, SIZE_Y, START}, Math::Vector3{0.0F, 0.0F, 0.0F}, Math::Vector2{TEXTURE_MAX_X, TEXTURE_MIN_Y}},
        Vertex{Math::Vector3{SIZE_X, SIZE_Y, START}, Math::Vector3{0.0F, 0.0F, 0.0F}, Math::Vector2{TEXTURE_MIN_X, TEXTURE_MIN_Y}},
        Vertex{Math::Vector3{SIZE_X, START, START}, Math::Vector3{0.0F, 0.0F, 0.0F}, Math::Vector2{TEXTURE_MIN_X, TEXTURE_MAX_Y}},
    };

    std::vector<int> indices{0, 1, 2,
        0, 2, 3,
        };

    Texture shoot_texture{};
    shoot_texture.id = load_texture("PISFA0.png", "res/textures");
    shoot_texture.path = "res/textures";
    shoot_texture.type = aiTextureType_DIFFUSE;

    Material shoot_material{};
    shoot_material.set_textures(std::vector<Texture>{shoot_texture});
    shoot_material_ = shoot_material;
    shoot_ = Mesh(vertices, indices, shoot_material_);

    shoot_transform_.set_translation(Math::Vector3{8.0F, 0.0F, 10.0F});
    shoot_transform_.set_projection(80, 1280, 720, 0.01F, 1000.0F);
    shoot_transform_.set_camera(camera_);

    Texture texture{};
    texture.id = load_texture("PISGB0.png", "res/textures");
    texture.path = "res/textures";
    texture.type = aiTextureType_DIFFUSE;

    Material material{};
    material.set_textures(std::vector<Texture>{texture});
    gun_material_ = material;
    gun_ = Mesh(vertices, indices, gun_material_);
    gun_transform_.set_translation(Math::Vector3{8.0F, 0.0F, 10.0F});
    gun_transform_.set_projection(80, 1280, 720, 0.01F, 1000.0F);
    gun_transform_.set_camera(camera_);
}

Game::Player::Player(const Math::Vector3& initial_position)
{
    Game::Player::camera_->set_position(initial_position);

    std::vector<Vertex> vertices{
        Vertex{Math::Vector3{-SIZE_X, START, START}, Math::Vector3{0.0F, 0.0F, 0.0F}, Math::Vector2{TEXTURE_MAX_X, TEXTURE_MAX_Y}},
        Vertex{Math::Vector3{-SIZE_X, SIZE_Y, START}, Math::Vector3{0.0F, 0.0F, 0.0F}, Math::Vector2{TEXTURE_MAX_X, TEXTURE_MIN_Y}},
        Vertex{Math::Vector3{SIZE_X, SIZE_Y, START}, Math::Vector3{0.0F, 0.0F, 0.0F}, Math::Vector2{TEXTURE_MIN_X, TEXTURE_MIN_Y}},
        Vertex{Math::Vector3{SIZE_X, START, START}, Math::Vector3{0.0F, 0.0F, 0.0F}, Math::Vector2{TEXTURE_MIN_X, TEXTURE_MAX_Y}},
    };

    std::vector<int> indices{0, 1, 2,
        0, 2, 3,
        };

    Texture texture{};
    texture.id = load_texture("PISGB0.png", "res/textures");
    texture.path = "res/textures";
    texture.type = aiTextureType_DIFFUSE;

    Material material{};
    material.set_textures(std::vector<Texture>{texture});
    gun_material_ = material;
    gun_ = Mesh(vertices, indices, gun_material_);
    gun_transform_.set_translation(Math::Vector3{8.0F, 0.0F, 10.0F});
    gun_transform_.set_projection(80, 1280, 720, 0.01F, 1000.0F);
    gun_transform_.set_camera(camera_);
}

Game::Player::Player(const Player& other)
{
    level_ = other.level_;
}

Game::Player& Game::Player::operator=(Game::Player&& player)
{
    return *this;
}

Game::Player& Game::Player::operator=(const Game::Player& player)
{
    return *this;
}

void Game::Player::input(const Input& inputs)
{
    if (inputs.is_key_down(SDLK_w)) {
        movement_vector_ = movement_vector_ + camera_->get_forward();
    }

    if (inputs.is_key_down(SDLK_s)) {
        movement_vector_ = movement_vector_ + (-1.0F * camera_->get_forward());
    }

    if (inputs.is_key_down(SDLK_d)) {
        movement_vector_ = movement_vector_ + camera_->get_right();
    }

    if (inputs.is_key_down(SDLK_a)) {
        movement_vector_ = movement_vector_ + camera_->get_left();
    }

    if (inputs.is_key_down(SDLK_DOWN)) {
        camera_->rotate_x(1.0F);
    }

    if (inputs.is_key_down(SDLK_UP)) {
        camera_->rotate_x(-1.0F);
    }

    if (inputs.is_key_down(SDLK_LEFT)) {
        camera_->rotate_y(-1.0F);
    }

    if (inputs.is_key_down(SDLK_RIGHT)) {
        camera_->rotate_y(1.0F);
    }

    if (inputs.is_key_just_pressed(SDLK_e)) {
        level_->open_doors(camera_->get_position(), true);
    }

    if (inputs.is_key_just_pressed(SDLK_RETURN)) {
        last_shot_ = std::chrono::steady_clock::now();
        Math::Vector2 line_start{camera_->get_position().x, camera_->get_position().z};
        Math::Vector2 cast_direction = Math::normalize(Math::Vector2{camera_->get_forward().x, camera_->get_forward().z});
        Math::Vector2 line_end = line_start + SHOOT_DISTANCE * cast_direction;

        bool hit = false;

        level_->check_intersection(line_start, line_end, hit, true);
    }
}

void Game::Player::update()
{
    movement_vector_.y = 0;

    if (Math::length(movement_vector_) > 0) {
        movement_vector_ = Math::normalize(movement_vector_);
    }

    Math::Vector3 old_position = camera_->get_position();
    Math::Vector3 new_position = old_position + speed_ * movement_vector_;

    Math::Vector3 collision_vector = level_->check_collision(old_position, new_position, size_, size_);
    movement_vector_ = movement_vector_ * collision_vector;

    if (Math::length(movement_vector_) > 0) {
        camera_->move(movement_vector_, speed_);
    }

    movement_vector_.x = 0;
    movement_vector_.y = 0;
    movement_vector_.z = 0;

    if (health_ > 100) {
        health_ = 100;
    }

    // Gun movement
    Math::Vector3 translation = gun_transform_.translation();
    Math::Vector3 shoot_translation = shoot_transform_.translation();

    translation = camera_->get_position() + 0.105F * camera_->get_forward();
    shoot_translation = camera_->get_position() + 0.085F * camera_->get_forward();
    translation.y += GUN_OFFSET;
    shoot_translation.y += GUN_OFFSET;

    gun_transform_.set_translation(translation);
    shoot_transform_.set_translation(shoot_translation);

    Math::Vector3 direction_to_camera = camera_->get_position() - gun_transform_.translation();
    float angle_to_face_camera = Math::to_degrees(std::atan(direction_to_camera.z /
                direction_to_camera.x));

    if (direction_to_camera.x < 0) {
        angle_to_face_camera += 180;
    }

    Math::Vector3 gun_rotation = gun_transform_.rotation();
    gun_rotation.y = angle_to_face_camera + 90;
    gun_transform_.set_rotation(gun_rotation);

    Math::Vector3 shoot_rotation = shoot_transform_.rotation();
    shoot_rotation.y = angle_to_face_camera + 90;
    shoot_transform_.set_rotation(shoot_rotation);
}

void Game::Player::set_level(Level* level)
{
    level_ = level;
}

void Game::Player::damage(const int amount)
{
    health_ -= amount;
    std::cout << "Health left: " << health_ << '\n';
}

void Game::Player::heal(const int amount)
{
    damage(-amount);
}

bool Game::Player::dead() const
{
    return health_ <= 0;
}

void Game::Player::render(BasicShader& shader)
{
    auto now = std::chrono::steady_clock::now();
    float time_since_last_shot = static_cast<float>(std::chrono::duration_cast<std::chrono::milliseconds>(now - last_shot_).count());

    shader.bind();
    if (time_since_last_shot < 200.0F) {
        shoot_.set_material(shoot_material_);
        shader.set_material(shoot_material_);
        shader.set_transformations(shoot_transform_.get_transformation(), shoot_transform_.get_projected_transformation());
        shoot_.draw(shader);
    } else {
        gun_.set_material(gun_material_);
        shader.set_material(gun_material_);
        shader.set_transformations(gun_transform_.get_transformation(), gun_transform_.get_projected_transformation());
        gun_.draw(shader);
    }
}

int Game::Player::health() const
{
    return health_;
}
