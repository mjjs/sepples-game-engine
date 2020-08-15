#include "camera.h"
#include "gemath.h"
#include "input.h"
#include "player.h"
#include "vector2.h"
#include "vector3.h"

#include <iostream>

Game::Player::Player(const Math::Vector3& initial_position)
{
    Game::Player::camera_->set_position(initial_position);
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
        level_->open_doors(camera_->get_position());
    }

    if (inputs.is_key_just_pressed(SDLK_RETURN)) {
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

    camera_->move(movement_vector_, speed_);

    movement_vector_.x = 0;
    movement_vector_.y = 0;
    movement_vector_.z = 0;

    if (health_ > 100) {
        health_ = 100;
    }
}

void Game::Player::set_level(std::shared_ptr<Level> level)
{
    level_ = level;
}

void Game::Player::damage(const int amount)
{
    health_ -= amount;

    std::cout << "Player health left: " << health_ << '\n';

    if (health_ <= 0) {
        std::cout << "Player died\n";
    }
}

bool Game::Player::dead() const
{
    return health_ <= 0;
}
