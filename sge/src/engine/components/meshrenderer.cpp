#include "engine/components/camera.h"
#include "engine/components/meshrenderer.h"
#include "engine/rendering/material.h"
#include "engine/rendering/mesh.h"
#include "engine/core/transform.h"
#include "engine/core/input.h"
#include "engine/rendering/shaders/shader.h"
#include "engine/math/matrix4.h"
#include "engine/rendering/renderingengine.h"

#include <memory>
#include <utility>

SGE::MeshRenderer::MeshRenderer(std::shared_ptr<Mesh>& mesh) :
    mesh_{mesh}
{
}

void SGE::MeshRenderer::render(
        const SGE::Transform& transform,
        Shader& shader,
        const SGE::RenderingEngine& rendering_engine
        )
{
    shader.bind();

    shader.update_uniforms(transform, mesh_->material(), rendering_engine);

    mesh_->draw(shader);
}
