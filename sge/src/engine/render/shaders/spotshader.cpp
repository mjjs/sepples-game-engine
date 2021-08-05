#include "spotshader.h"

#include "material.h"
#include "renderingengine.h"
#include "shader.h"
#include "spotlight.h"
#include "transform.h"
#include "vector3.h"

namespace SGE
{

SpotShader::SpotShader()
    : Shader{"res/shaders/spot_light_vertex.glsl",
             "res/shaders/spot_light_fragment.glsl"}
{
}

void SpotShader::update_uniforms(const Transform& transform,
                                 const Material& material,
                                 const RenderingEngine& rendering_engine) const
{
    set_uniform("transform_u", transform.get_transformation());

    set_uniform("material_u.shininess", material.shininess());

    // set_uniform("view_position_u",
    //            rendering_engine.camera()->transform().position());

    // auto* light = dynamic_cast<SpotLight*>(rendering_engine.active_light());
    // if (light == nullptr) {
    //    throw std::runtime_error{"A spot light has malfunctioned."};
    //}

    // set_uniform("spot_light_u.base.colour", light->colour());
    // set_uniform("spot_light_u.base.intensity", light->intensity());
    // set_uniform("spot_light_u.position", transform.position());
    // set_uniform("spot_light_u.direction", light->direction());
    // set_uniform("spot_light_u.attenuation.constant", light->constant());
    // set_uniform("spot_light_u.attenuation.linear", light->linear());
    // set_uniform("spot_light_u.attenuation.quadratic", light->quadratic());
    // set_uniform("spot_light_u.cut_off", light->cut_off());
    // set_uniform("spot_light_u.outer_cut_off", light->outer_cut_off());
}

} // namespace SGE
