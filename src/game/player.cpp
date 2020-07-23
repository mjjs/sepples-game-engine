#include "camera.h"
#include "gemath.h"
#include "input.h"
#include "player.h"
#include "vector3.h"

Game::Player::Player(const Math::Vector3& initial_position) :
    camera_(std::make_shared<Camera>(initial_position, Math::Vector3{0.0F, 0.0F, 1.0F}, Math::Vector3{0.0F, 1.0F, 0.0F}))
{}

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
}

std::shared_ptr<Camera> Game::Player::camera() const
{
    return camera_;
}

void Game::Player::set_level(std::shared_ptr<Level> level)
{
    level_ = level;
}
