#include <assert.h>
#include "ambientlight.h"
#include "camera.h"
#include "sgemath.h"
#include "gamecomponent.h"
#include "directionallight.h"
#include "spotlight.h"
#include "pointlight.h"
#include "material.h"
#include "mesh.h"
#include "meshrenderer.h"
#include "model.h"
#include "modelrenderer.h"
#include "testgame.h"
#include "texture.h"
#include "vector3.h"
#include "transform.h"
#include "vertex.h"
#include "quaternion.h"

#include <cstdint>
#include <memory>
#include <vector>

std::shared_ptr<SGE::GameObject> get_lights();

TestGame::TestGame()
{
    SGE::Transform transform{};
    root()->set_transform(transform);
}

std::shared_ptr<SGE::GameObject> get_lights()
{
    auto light_object = std::make_shared<SGE::GameObject>();
    auto ambient_light = std::make_shared<SGE::AmbientLight>(0.2F);
    auto directional_light_blue = std::make_shared<SGE::DirectionalLight>(
            SGE::Vector3{0.0F, 0.0F, 1.0F},
            .5F
            );

    auto point_light = std::make_shared<SGE::PointLight>(
            SGE::Vector3{0, 1.0F, 0},
            2.0F,
            1,
            0,
            1
            );

    auto spot_light = std::make_shared<SGE::SpotLight>(
            SGE::Vector3{1, 1, 1},
            1.0F,
            std::cos(SGE::to_radians(12.5F)),
            std::cos(SGE::to_radians(17.5F)),
            1.0F,
            0.09F,
            0.032F
            );

    light_object->add_component(ambient_light);
    light_object->add_component(directional_light_blue);
    light_object->add_component(point_light);
    light_object->add_component(spot_light);

    light_object->transform().set_position(SGE::Vector3{5, 0, 0});
    light_object->transform()
        .set_rotation(SGE::Quaternion::euler(0, -90, 0));

    return light_object;
}

void TestGame::init()
{
    std::vector<SGE::Vertex> vertices = {
        {{-10, -2, -10}, {0, 1, 0}, {0, 0}},
        {{-10, -2, 30}, {0, 1, 0}, {0, 1}},
        {{30, -2, -10}, {0, 1, 0}, {1, 0}},
        {{30, -2, 30}, {0, 1, 0}, {1, 1}},
    };

    std::vector<SGE::Vertex> small_vertices = {
        {{-5, 2, -5}, {0, 1, 0}, {0, 0}},
        {{-5, 2, 10}, {0, 1, 0}, {0, 1}},
        {{10, 2, -5}, {0, 1, 0}, {1, 0}},
        {{10, 2, 10}, {0, 1, 0}, {1, 1}},
    };

    std::vector<std::uint32_t> indices = {0, 1, 2, 2, 1, 3};

    auto default_texture = SGE::load_diffuse_texture("defaultTexture.png", "res/textures");

    auto floor = std::make_shared<SGE::Mesh>(
        vertices,
        indices,
        SGE::Material{
            std::vector<SGE::Texture>{default_texture},
            SGE::Vector3{.5F, 1.0F, 1.0F},
            SGE::Vector3{.3F, 1.0F, 1.0F},
            SGE::Vector3{.8F, .8F, .8F}
        }
    );

    auto small_floor = std::make_shared<SGE::Mesh>(
        small_vertices,
        indices,
        SGE::Material{
            std::vector<SGE::Texture>{default_texture},
            SGE::Vector3{.5F, 1.0F, 1.0F},
            SGE::Vector3{.3F, 1.0F, 1.0F},
            SGE::Vector3{.8F, .8F, .8F}
        }
    );

    auto small_floor_go = std::make_shared<SGE::GameObject>();
    auto small_floor_go_2 = std::make_shared<SGE::GameObject>();
    small_floor_go->add_component(
            std::make_shared<SGE::MeshRenderer>(small_floor)
    );
    small_floor_go_2->add_component(
            std::make_shared<SGE::MeshRenderer>(small_floor)
    );

    small_floor_go->add_child(small_floor_go_2);

    small_floor_go
        ->transform()
        .set_position(SGE::Vector3{0, 2, 0});
    small_floor_go_2
        ->transform()
        .set_position(SGE::Vector3{0, 0, 15});

    small_floor_go
        ->transform()
        .set_rotation(SGE::Quaternion::euler(0, 30, 0));

    small_floor_go_2
        ->transform()
        .set_rotation(SGE::Quaternion::euler(0, -45, 0));

    root()->add_component(std::make_shared<SGE::MeshRenderer>(floor));
    root()->add_child(small_floor_go);

    auto model_renderer_object = std::make_shared<SGE::GameObject>();
    auto model_renderer = std::make_shared<SGE::ModelRenderer>(SGE::Model("res/models/backpack.obj"));
    model_renderer_object->add_component(model_renderer);

    model_renderer_object->
        transform().set_rotation(SGE::Quaternion::euler(30, 45, 90));

    root()->add_child(model_renderer_object);

    std::shared_ptr<SGE::GameObject> lights = get_lights();

    root()->add_child(lights);

    auto child = std::make_shared<SGE::GameObject>();
    auto camera = std::make_shared<SGE::Camera>(
            SGE::to_radians(70),
            static_cast<float>(1270)/static_cast<float>(800),
            .1,
            1000
            );

    child->add_component(camera);
    root()->add_child(child);
}
