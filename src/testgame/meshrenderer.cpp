#include "camera.h"
#include "meshrenderer.h"
#include "material.h"
#include "mesh.h"
#include "transform.h"
#include "input.h"
#include "shader.h"
#include "matrix4.h"
#include "renderingengine.h"

MeshRenderer::MeshRenderer(const Mesh& mesh) :
    mesh_{mesh}
{
}

void MeshRenderer::render(const Math::Transform& transform, Shader& shader, const SGE::RenderingEngine& rendering_engine)
{
    shader.bind();

    shader.update_uniforms(transform, mesh_.material(), rendering_engine);

    mesh_.draw(shader);
}
