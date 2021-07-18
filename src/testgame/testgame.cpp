#include "ambientlight.h"
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

#include <memory>
#include <vector>

SGE::GameObject get_lights();

TestGame::TestGame()
{
    Math::Transform transform{};
    root()->set_transform(transform);
}

SGE::GameObject get_lights()
{
    SGE::GameObject light_object{};

    light_object.add_component(std::make_shared<SGE::AmbientLight>(0.2F));

    light_object.add_component(std::make_shared<SGE::DirectionalLight>(
        Math::Vector3{8.0F, 0.0F, 5.0F},
        Math::Vector3{0.0F, 0.0F, 1.0F},
        .2F
    ));

    light_object.add_component(std::make_shared<SGE::DirectionalLight>(
        Math::Vector3{-8.0F, 0.0F, -5.0F},
        Math::Vector3{1.0F, 0.0F, 0.0F},
        .2F
    ));

    light_object.add_component(std::make_shared<SGE::PointLight>(
        SGE::PointLight{
            Math::Vector3{5, 0, 5},
            Math::Vector3{0, 1.0F, 0},
            2.0F,
            1,
            0,
            1,
        }
    ));

    return light_object;
}

void TestGame::init()
{
    std::vector<Vertex> vertices = {
        {{-10, -2, -10}, {0, 1, 0}, {0, 0}},
        {{-10, -2, 30}, {0, 1, 0}, {0, 1}},
        {{30, -2, -10}, {0, 1, 0}, {1, 0}},
        {{30, -2, 30}, {0, 1, 0}, {1, 1}},
    };

    std::vector<int> indices = {0, 1, 2, 2, 1, 3};
    Mesh floor{
        vertices,
        indices,
        Material{
            //std::vector<Texture>{load_diffuse_texture("test.jpg", "res/textures")},
            Math::Vector3{.5F, 1.0F, 1.0F},
            Math::Vector3{.3F, 1.0F, 1.0F},
            Math::Vector3{.8F, .8F, .8F}
        },
    };

    root()->add_component(std::make_shared<MeshRenderer>(floor));
    root()->add_component(std::make_shared<ModelRenderer>(Model("res/models/backpack.obj")));

    SGE::GameObject lights = get_lights();
    //lights.set_transform(root()->transform());

    root()->add_child(std::make_shared<SGE::GameObject>(lights));
}
