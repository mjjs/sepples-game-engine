#include "camera.h"
#include "model.h"
#include "modelrenderer.h"
#include "transform.h"
#include "input.h"
#include "shader.h"
#include "renderingengine.h"

SGE::ModelRenderer::ModelRenderer(const SGE::Model& model) : model_{model}
{
}

void SGE::ModelRenderer::render(
        const SGE::Math::Transform& transform,
        Shader& shader,
        const SGE::RenderingEngine& rendering_engine
        )
{
    shader.bind();
    shader.update_uniforms(transform, Material{}, rendering_engine);

    model_.draw(shader);
}
