#include "camera.h"
#include "model.h"
#include "modelrenderer.h"
#include "transform.h"
#include "input.h"
#include "shader.h"

ModelRenderer::ModelRenderer(const Model& model) : model_{model}
{
}

void ModelRenderer::render(const Math::Transform& transform, Shader& shader, const Camera& camera)
{
    shader.bind();
    shader.set_transformations(transform.get_transformation(),
            transform.get_projected_transformation(camera));

    model_.draw(shader);
}
