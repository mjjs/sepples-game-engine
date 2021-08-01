#include "basicshader.h"
#include "shader.h"
#include "renderingengine.h"
#include "transform.h"
#include "material.h"

namespace SGE {

BasicShader::BasicShader() :
    Shader{"res/shaders/basic_vertex.glsl", "res/shaders/basic_fragment.glsl"}
{
}

void BasicShader::update_uniforms(
        const Transform& transform,
        const Material& material,
        const RenderingEngine& rendering_engine) const
{
    set_uniform("transform_u", transform.get_projected_transformation(*rendering_engine.camera()));

    set_uniform("material_u.ambient", material.ambient_colour());
    set_uniform("material_u.diffuse", material.diffuse_colour());
    set_uniform("material_u.specular", material.specular_colour());
    set_uniform("material_u.shininess", material.shininess());
}

} // namespace SGE
