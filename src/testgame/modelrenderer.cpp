#include "model.h"
#include "modelrenderer.h"
#include "transform.h"
#include "input.h"
#include "shader.h"

ModelRenderer::ModelRenderer(const Model& model) : model_{model}
{
}

void ModelRenderer::render(const Math::Transform& transform, Shader& shader)
{
    shader.bind();
    shader.set_transformations(transform.get_transformation(),
            transform.get_projected_transformation());

    model_.draw(shader);
}

void ModelRenderer::input(const Input& input, const Math::Transform& transform)
{
}

void ModelRenderer::update(const Math::Transform& transform)
{
}

void ModelRenderer::init()
{
}
