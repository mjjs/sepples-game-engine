#include "spotshader.h"
#include "material.h"
#include "transform.h"
#include "shader.h"
#include "vector3.h"
#include "spotlight.h"
#include "renderingengine.h"

namespace SGE {

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
        const RenderingEngine& rendering_engine)
{
    set_uniform("transform_u", transform.get_projected_transformation(rendering_engine.camera()));
    set_uniform("projection_u", transform.get_transformation());

    set_uniform("material_u.ambient", material.ambient_colour());
    set_uniform("material_u.diffuse", material.diffuse_colour());
    set_uniform("material_u.specular", material.specular_colour());
    set_uniform("material_u.shininess", material.shininess());

    set_uniform("view_position_u", rendering_engine.camera().get_position());

    auto* light = dynamic_cast<SpotLight*>(rendering_engine.active_light());
    if (light == nullptr) {
        throw std::runtime_error{"A spot light has malfunctioned."};
    }

    Math::Transform t = transform;

    set_uniform("spot_light_u.base.colour", light->colour());
    set_uniform("spot_light_u.base.intensity", light->intensity());
    set_uniform("spot_light_u.position", t.position());
    set_uniform("spot_light_u.direction", light->direction());
    set_uniform("spot_light_u.attenuation.constant", light->constant());
    set_uniform("spot_light_u.attenuation.linear", light->linear());
    set_uniform("spot_light_u.attenuation.quadratic", light->quadratic());
    set_uniform("spot_light_u.cut_off", light->cut_off());
    set_uniform("spot_light_u.outer_cut_off", light->outer_cut_off());
}

} // namespace SGE
