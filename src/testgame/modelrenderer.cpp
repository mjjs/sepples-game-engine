#include "model.h"
#include "modelrenderer.h"
#include "transform.h"

ModelRenderer::ModelRenderer(const Model& model) : model_{model}
{
}

void ModelRenderer::render(const Math::Transform& transform)
{
    shader_.bind();
    shader_.set_transformations(transform.get_transformation(),
            transform.get_projected_transformation());

    model_.draw(shader_);
}

void ModelRenderer::input(const Math::Transform& transform)
{
}

void ModelRenderer::update(const Math::Transform& transform)
{
}

void ModelRenderer::init()
{
}
