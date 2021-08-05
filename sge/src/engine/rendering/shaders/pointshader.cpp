#include "engine/rendering/shaders/pointshader.h"

#include "engine/rendering/material.h"
#include "engine/components/pointlight.h"
#include "engine/rendering/renderingengine.h"
#include "engine/rendering/shaders/shader.h"
#include "engine/core/transform.h"
#include "engine/math/vector3.h"

namespace SGE
{

PointShader::PointShader()
    : Shader{"res/shaders/point_light_vertex.glsl",
             "res/shaders/point_light_fragment.glsl"}
{
}

void PointShader::update_uniforms(const Transform& transform,
                                  const Material& material,
                                  const RenderingEngine& rendering_engine) const
{
    set_uniform("transform_u", transform.get_transformation());

    // set_uniform("view_position_u",
    //            rendering_engine.camera()->transform().position());

    set_uniform("material_u.shininess", material.shininess());

    // auto* light = dynamic_cast<PointLight*>(rendering_engine.active_light());
    // if (light == nullptr) {
    //    throw std::runtime_error{"A point light has malfunctioned."};
    //}

    // set_uniform("point_light_u.position", light->get_transform().position());
    // set_uniform("point_light_u.base.colour", light->colour());
    // set_uniform("point_light_u.base.intensity", light->intensity());
    // set_uniform("point_light_u.attenuation.constant", light->constant());
    // set_uniform("point_light_u.attenuation.linear", light->linear());
    // set_uniform("point_light_u.attenuation.quadratic", light->quadratic());
}

} // namespace SGE
