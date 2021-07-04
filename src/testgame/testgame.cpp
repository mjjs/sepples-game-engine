#include "gamecomponent.h"
#include "material.h"
#include "mesh.h"
#include "meshrenderer.h"
#include "model.h"
#include "modelrenderer.h"
#include "testgame.h"
#include "texture.h"
#include "transform.h"
#include "vertex.h"

#include <vector>

TestGame::TestGame()
{
    Math::Transform transform{};

    root()->set_transform(transform);

    std::vector<Vertex> vertices = {
        {{-10, -2, -10}, {0, 0}, {0, 0}},
        {{-10, -2, 30}, {0, 0}, {0, 1}},
        {{30, -2, -10}, {0, 0}, {1, 0}},
        {{30, -2, 30}, {0, 0}, {1, 1}},
    };

    std::vector<int> indices = {0, 1, 2, 2, 1, 3};
    Mesh floor{
        vertices,
        indices,
        Material{{.5F, 0.0F, 0.0F}, {.3F, 1.0F, 1.0F}, {0.0F, 0.0F, 0.0F}},
    };

    root()->add_component(std::make_shared<MeshRenderer>(floor));
    root()->add_component(std::make_shared<ModelRenderer>(Model("res/models/backpack.obj")));
}

void TestGame::init()
{
}
