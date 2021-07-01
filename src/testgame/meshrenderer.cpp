#include "camera.h"
#include "meshrenderer.h"
#include "material.h"
#include "mesh.h"
#include "transform.h"
#include "input.h"
#include "shader.h"
#include "matrix4.h"

MeshRenderer::MeshRenderer(const Mesh& mesh, const Material& material) :
    mesh_{mesh},
    material_{material}
{
}

void MeshRenderer::render(const Math::Transform& transform, Shader& shader, const Camera& camera)
{
    shader.bind();

    shader.set_transformations(transform.get_transformation(),
            transform.get_projected_transformation(camera));

    mesh_.draw(shader);
}

void MeshRenderer::input(const Input& input, const Math::Transform& transform)
{
}

void MeshRenderer::update(const Math::Transform& transform)
{
}

void MeshRenderer::init()
{
}
