#include "engine/rendering/shaders/basicshader.h"

#include "engine/rendering/material.h"
#include "engine/rendering/renderingengine.h"
#include "engine/rendering/shaders/shader.h"
#include "engine/core/transform.h"

namespace SGE
{

BasicShader::BasicShader()
    : Shader{"res/shaders/basic_vertex.glsl", "res/shaders/basic_fragment.glsl"}
{
}

void BasicShader::update_uniforms(
    const Transform& transform, const Material& material,
    [[maybe_unused]] const RenderingEngine& rendering_engine) const
{
    set_uniform("transform_u", transform.get_transformation());

    set_uniform("material_u.shininess", material.shininess());
}

} // namespace SGE
