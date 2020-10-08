#include "meshrenderer.h"
#include "material.h"
#include "mesh.h"
#include "transform.h"

MeshRenderer::MeshRenderer(const Mesh& mesh, const Material& material) :
    mesh_{mesh},
    material_{material}
{
}

void MeshRenderer::render(const Math::Transform& transform)
{
    shader_.bind();
    shader_.set_transformations(transform.get_transformation(),
            transform.get_projected_transformation());

    mesh_.draw(shader_);
}

void MeshRenderer::input(const Math::Transform& transform)
{
}

void MeshRenderer::update(const Math::Transform& transform)
{
}

void MeshRenderer::init()
{
}
