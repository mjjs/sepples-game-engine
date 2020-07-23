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
    Math::Vector3 movement_vector{0.0F, 0.0F, 0.0F};

    if (inputs.is_key_down(SDLK_w)) {
        movement_vector = movement_vector + camera_->get_forward();
    }

    if (inputs.is_key_down(SDLK_s)) {
        movement_vector = movement_vector + (-1.0F * camera_->get_forward());
    }

    if (inputs.is_key_down(SDLK_d)) {
        movement_vector = movement_vector + camera_->get_right();
    }

    if (inputs.is_key_down(SDLK_a)) {
        movement_vector = movement_vector + camera_->get_left();
    }

    if (Math::length(movement_vector) > 0) {
        movement_vector.y = 0;
        camera_->move(Math::normalize(movement_vector), speed_);
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

std::shared_ptr<Camera> Game::Player::camera() const
{
    return camera_;
}
