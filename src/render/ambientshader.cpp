#include "ambientshader.h"
#include "material.h"
#include "transform.h"
#include "shader.h"
#include "vector3.h"
#include "renderingengine.h"

AmbientShader::AmbientShader() :
    Shader{"res/shaders/ambient_light_vertex.glsl", "res/shaders/ambient_light_fragment.glsl"}
{
    add_uniform("transform_u");

    add_uniform("material_u.ambient");
    add_uniform("material_u.diffuse");
    add_uniform("material_u.specular");
    add_uniform("material_u.shininess");

    add_uniform("intensity_u");
}

void AmbientShader::update_uniforms(
        const Math::Transform& transform,
        const Material& material,
        const SGE::RenderingEngine& rendering_engine)
{
    set_uniform("transform_u", transform.get_projected_transformation(rendering_engine.camera()));

    set_uniform("material_u.ambient", material.ambient_colour());
    set_uniform("material_u.diffuse", material.diffuse_colour());
    set_uniform("material_u.specular", material.specular_colour());
    set_uniform("material_u.shininess", material.shininess());

    set_uniform("intensity_u", rendering_engine.ambient_light());
}
