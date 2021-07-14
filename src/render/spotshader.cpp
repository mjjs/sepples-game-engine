#include "spotshader.h"
#include "material.h"
#include "transform.h"
#include "shader.h"
#include "vector3.h"
#include "renderingengine.h"

SpotShader::SpotShader() :
    Shader{"res/shaders/spot_light_vertex.glsl", "res/shaders/spot_light_fragment.glsl"}
{
    add_uniform("transform_u");
    add_uniform("projection_u");

    add_uniform("spot_light_u.base.colour");
    add_uniform("spot_light_u.base.intensity");
    add_uniform("spot_light_u.position");
    add_uniform("spot_light_u.direction");
    add_uniform("spot_light_u.attenuation.constant");
    add_uniform("spot_light_u.attenuation.linear");
    add_uniform("spot_light_u.attenuation.quadratic");
    add_uniform("spot_light_u.cut_off");
    add_uniform("spot_light_u.outer_cut_off");

    add_uniform("view_position_u");

    add_uniform("material_u.ambient");
    add_uniform("material_u.diffuse");
    add_uniform("material_u.specular");
    add_uniform("material_u.shininess");
}

void SpotShader::update_uniforms(
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

    set_uniform("spot_light_u.base.colour", rendering_engine.spot_light.colour);
    set_uniform("spot_light_u.base.intensity", rendering_engine.spot_light.intensity);
    set_uniform("spot_light_u.position", rendering_engine.spot_light.position);
    set_uniform("spot_light_u.direction", rendering_engine.spot_light.direction);
    set_uniform("spot_light_u.attenuation.constant", rendering_engine.spot_light.constant);
    set_uniform("spot_light_u.attenuation.linear", rendering_engine.spot_light.linear);
    set_uniform("spot_light_u.attenuation.quadratic", rendering_engine.spot_light.quadratic);
    set_uniform("spot_light_u.cut_off", rendering_engine.spot_light.cut_off);
    set_uniform("spot_light_u.outer_cut_off", rendering_engine.spot_light.outer_cut_off);
}
