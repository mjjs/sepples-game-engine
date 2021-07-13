#include "directionalshader.h"
#include "material.h"
#include "transform.h"
#include "shader.h"
#include "vector3.h"
#include "renderingengine.h"

DirectionalShader::DirectionalShader() :
    Shader{"res/shaders/directional_light_vertex.glsl", "res/shaders/directional_light_fragment.glsl"}
{
    add_uniform("transform_u");
    add_uniform("projection_u");

    add_uniform("directional_light_u.direction");
    add_uniform("directional_light_u.base.colour");
    add_uniform("directional_light_u.base.intensity");

    add_uniform("view_position_u");

    add_uniform("material_u.ambient");
    add_uniform("material_u.diffuse");
    add_uniform("material_u.specular");
    add_uniform("material_u.shininess");
}

void DirectionalShader::update_uniforms(
        const Math::Transform& transform,
        const Material& material,
        const SGE::RenderingEngine& rendering_engine)
{
    set_uniform("transform_u", transform.get_projected_transformation(rendering_engine.camera()));
    set_uniform("projection_u", transform.get_transformation());

    set_uniform("material_u.ambient", material.ambient_colour());
    set_uniform("material_u.diffuse", material.diffuse_colour());
    set_uniform("material_u.specular", material.specular_colour());
    set_uniform("material_u.shininess", material.shininess());

    set_uniform("view_position_u", rendering_engine.camera().get_position());

    set_uniform("directional_light_u.direction", rendering_engine.directional_light.direction);
    set_uniform("directional_light_u.base.colour", rendering_engine.directional_light.colour);
    set_uniform("directional_light_u.base.intensity", rendering_engine.directional_light.intensity);
}
