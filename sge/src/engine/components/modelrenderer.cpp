#include "engine/components/camera.h"
#include "engine/rendering/model.h"
#include "engine/components/modelrenderer.h"
#include "engine/core/transform.h"
#include "engine/core/input.h"
#include "engine/rendering/shaders/shader.h"
#include "engine/rendering/renderingengine.h"

SGE::ModelRenderer::ModelRenderer(const SGE::Model& model) : model_{model}
{
}

void SGE::ModelRenderer::render(
        const SGE::Transform& transform,
        Shader& shader,
        const SGE::RenderingEngine& rendering_engine
        )
{
    shader.bind();
    shader.update_uniforms(transform, Material{}, rendering_engine);

    model_.draw(shader);
}
