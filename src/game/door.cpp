#include "basicshader.h"
#include "door.h"
#include "material.h"
#include "mesh.h"
#include "transform.h"
#include "vector2.h"
#include "vector3.h"
#include "vertex.h"

#include <chrono>
#include <vector>

#include <iostream>

Game::Door::Door(const Math::Transform& transform, const Material& material, const Math::Vector3& open_position) :
    transform_{transform},
    material_{material}
{
    close_position_ = transform.translation();
    open_position_ = open_position;

    if (!Game::Door::mesh_created) {
        std::vector<Vertex> vertices{
            Vertex{Math::Vector3{START, START, START}, Math::Vector3{0.0F, 0.0F, 0.0F}, Math::Vector2{0.5F, 1.0F}},
            Vertex{Math::Vector3{START, HEIGHT, START}, Math::Vector3{0.0F, 0.0F, 0.0F}, Math::Vector2{0.5F, 0.75F}},
            Vertex{Math::Vector3{LENGTH, HEIGHT, START}, Math::Vector3{0.0F, 0.0F, 0.0F}, Math::Vector2{0.75F, 0.75F}},
            Vertex{Math::Vector3{LENGTH, START, START}, Math::Vector3{0.0F, 0.0F, 0.0F}, Math::Vector2{0.75F, 1.0F}},

            Vertex{Math::Vector3{START, START, START}, Math::Vector3{0.0F, 0.0F, 0.0F}, Math::Vector2{0.73F, 1.0F}},
            Vertex{Math::Vector3{START, HEIGHT, START}, Math::Vector3{0.0F, 0.0F, 0.0F}, Math::Vector2{0.73F, 0.75F}},
            Vertex{Math::Vector3{START, HEIGHT, WIDTH}, Math::Vector3{0.0F, 0.0F, 0.0F}, Math::Vector2{0.75F, 0.75F}},
            Vertex{Math::Vector3{START, START, WIDTH}, Math::Vector3{0.0F, 0.0F, 0.0F}, Math::Vector2{0.75F, 1.0F}},

            Vertex{Math::Vector3{START, START, WIDTH}, Math::Vector3{0.0F, 0.0F, 0.0F}, Math::Vector2{0.5F, 1.0F}},
            Vertex{Math::Vector3{START, HEIGHT, WIDTH}, Math::Vector3{0.0F, 0.0F, 0.0F}, Math::Vector2{0.5F, 0.75F}},
            Vertex{Math::Vector3{LENGTH, HEIGHT, WIDTH}, Math::Vector3{0.0F, 0.0F, 0.0F}, Math::Vector2{0.75F, 0.75F}},
            Vertex{Math::Vector3{LENGTH, START, WIDTH}, Math::Vector3{0.0F, 0.0F, 0.0F}, Math::Vector2{0.75F, 1.0F}},

            Vertex{Math::Vector3{LENGTH, START, START}, Math::Vector3{0.0F, 0.0F, 0.0F}, Math::Vector2{0.73F, 1.0F}},
            Vertex{Math::Vector3{LENGTH, HEIGHT, START}, Math::Vector3{0.0F, 0.0F, 0.0F}, Math::Vector2{0.73F, 0.75F}},
            Vertex{Math::Vector3{LENGTH, HEIGHT, WIDTH}, Math::Vector3{0.0F, 0.0F, 0.0F}, Math::Vector2{0.75F, 0.75F}},
            Vertex{Math::Vector3{LENGTH, START, WIDTH}, Math::Vector3{0.0F, 0.0F, 0.0F}, Math::Vector2{0.75F, 1.0F}}

        };

        std::vector<int> indices{0, 1, 2,
            0, 2, 3,

            6, 5, 4,
            7, 6, 4,

            10, 9, 8,
            11, 10, 8,

            12, 13, 14,
            12, 14, 15};

        Game::Door::mesh = Mesh(vertices, indices, material_);
        mesh_created = true;
    }
}

void Game::Door::update()
{
    if (!is_opening_) {
        return;
    }

    auto now = std::chrono::steady_clock::now();

    if (now < open_time_) {
        float lerp_factor = static_cast<float>(std::chrono::duration_cast<std::chrono::milliseconds>(now - open_start_time_).count()) / DOOR_OPEN_TIME_.count();
        transform_.set_translation(interpolate_lerp(close_position_, open_position_, lerp_factor));
    } else if (now < closing_start_time_){
        transform_.set_translation(open_position_);
    } else if (now < close_time_) {
        float lerp_factor = static_cast<float>(std::chrono::duration_cast<std::chrono::milliseconds>(now - closing_start_time_).count()) / DOOR_OPEN_TIME_.count();
        transform_.set_translation(interpolate_lerp(open_position_, close_position_, lerp_factor));
    } else {
        transform_.set_translation(close_position_);
        is_opening_ = false;
    }
}

void Game::Door::render(BasicShader& shader)
{
    shader.set_transformations(transform_.get_transformation(), transform_.get_projected_transformation());
    Game::Door::mesh.draw(shader);
}

Math::Transform& Game::Door::transform()
{
    return transform_;
}

void Game::Door::open()
{
    if (is_opening_) {
        return;
    }

    open_start_time_ = std::chrono::steady_clock::now();
    open_time_ = open_start_time_ + DOOR_OPEN_TIME_;

    closing_start_time_ = open_start_time_ + DOOR_CLOSE_DELAY_;
    close_time_ = closing_start_time_ + DOOR_OPEN_TIME_;

    is_opening_ = true;
}

Math::Vector3 Game::Door::interpolate_lerp(const Math::Vector3& start, const Math::Vector3& end, float factor)
{
    return start + factor * (end - start);
}

Math::Vector2 Game::Door::size() const
{
    if (transform_.rotation().y == 90) {
        return Math::Vector2{WIDTH, LENGTH};
    }

    return Math::Vector2{LENGTH, WIDTH};
}
