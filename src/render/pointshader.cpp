#include "pointshader.h"
#include "material.h"
#include "transform.h"
#include "shader.h"
#include "vector3.h"
#include "renderingengine.h"

PointShader::PointShader() :
    Shader{"res/shaders/point_light_vertex.glsl", "res/shaders/point_light_fragment.glsl"}
{
    add_uniform("transform_u");
    add_uniform("projection_u");

    add_uniform("point_light_u.position");
    add_uniform("point_light_u.base.colour");
    add_uniform("point_light_u.base.intensity");
    add_uniform("point_light_u.attenuation.constant");
    add_uniform("point_light_u.attenuation.linear");
    add_uniform("point_light_u.attenuation.quadratic");

    add_uniform("view_position_u");

    add_uniform("material_u.ambient");
    add_uniform("material_u.diffuse");
    add_uniform("material_u.specular");
    add_uniform("material_u.shininess");
}

void PointShader::update_uniforms(
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

    set_uniform("point_light_u.position", rendering_engine.point_light.position);
    set_uniform("point_light_u.base.colour", rendering_engine.point_light.colour);
    set_uniform("point_light_u.base.intensity", rendering_engine.point_light.intensity);
    set_uniform("point_light_u.attenuation.constant", rendering_engine.point_light.constant);
    set_uniform("point_light_u.attenuation.linear", rendering_engine.point_light.linear);
    set_uniform("point_light_u.attenuation.quadratic", rendering_engine.point_light.quadratic);

    set_uniform("directional_light_u.direction", rendering_engine.directional_light.direction);
    set_uniform("directional_light_u.base.colour", rendering_engine.directional_light.colour);
    set_uniform("directional_light_u.base.intensity", rendering_engine.directional_light.intensity);
}
