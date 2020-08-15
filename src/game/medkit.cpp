#include "medkit.h"

#include "basicshader.h"
#include "gemath.h"
#include "material.h"
#include "mesh.h"
#include "player.h"
#include "transform.h"
#include "vector3.h"

#include "resourceloader.h"

#include <iostream>


Game::Medkit::Medkit(const Math::Transform& transform, Player* player) :
    transform_(transform)
{
    player_ = player;

    if (!mesh_created_) {
        // Create it
        Texture texture{};
        texture.id = load_texture("MEDIA0.png", "res/textures");
        texture.path = "res/textures";
        texture.type = aiTextureType_DIFFUSE;

        Material material{};
        material.set_textures(std::vector<Texture>{texture});
        material_ = material;

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

Game::Medkit& Game::Medkit::operator=(Medkit&& medkit)
{
    used_ = medkit.used();
    player_ = medkit.player_;
    medkit.player_ = nullptr;
    transform_ = medkit.transform_;
    return *this;
}

Game::Medkit::Medkit(const Medkit& medkit)
{
    player_ = medkit.player_;
    material_ = medkit.material_;
    transform_ = medkit.transform_;
    used_ = medkit.used_;
}

void Game::Medkit::render(BasicShader& shader)
{
    mesh_.set_material(material_);
    shader.set_material(material_);
    shader.set_transformations(transform_.get_transformation(), transform_.get_projected_transformation());
    mesh_.draw(shader);
}

void Game::Medkit::update()
{
    Math::Vector3 direction_to_camera = transform_.get_camera()->get_position() - transform_.translation();
    float angle_to_face_camera = Math::to_degrees(std::atan(direction_to_camera.z /
                direction_to_camera.x));

    if (direction_to_camera.x < 0) {
        angle_to_face_camera += 180;
    }

    Math::Vector3 rotation = transform_.rotation();
    rotation.y = angle_to_face_camera + 90;
    transform_.set_rotation(rotation);

    if (Math::length(direction_to_camera) < PICKUP_DISTANCE) {
        if (player_->health() < 100) {
            player_->heal(30);
            used_ = true;
        }
    }
}

Math::Transform& Game::Medkit::transform()
{
    return transform_;
}

bool Game::Medkit::used()
{
    return used_;
}
