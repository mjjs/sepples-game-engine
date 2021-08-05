#include "engine/rendering/shaders/directionalshader.h"

#include "engine/components/directionallight.h"
#include "engine/rendering/material.h"
#include "engine/rendering/renderingengine.h"
#include "engine/rendering/shaders/shader.h"
#include "engine/core/transform.h"
#include "engine/math/vector3.h"

namespace SGE
{

DirectionalShader::DirectionalShader()
    : Shader{"res/shaders/directional_light_vertex.glsl",
             "res/shaders/directional_light_fragment.glsl"}
{
}

void DirectionalShader::update_uniforms(
    const Transform& transform, const Material& material,
    const RenderingEngine& rendering_engine) const
{
    set_uniform("transform_u", transform.get_transformation());

    set_uniform("material_u.shininess", material.shininess());

    // set_uniform("view_position_u",
    //            rendering_engine.camera()->transform().position());

    // auto* light =
    //    dynamic_cast<DirectionalLight*>(rendering_engine.active_light());

    // if (light == nullptr) {
    //    throw std::runtime_error{"A directional light has malfunctioned."};
    //}

    // set_uniform("directional_light_u.direction", light->direction());
    // set_uniform("directional_light_u.base.colour", light->colour());
    // set_uniform("directional_light_u.base.intensity", light->intensity());
}

} // namespace SGE
