#include "engine/rendering/shaders/ambientshader.h"

#include "engine/components/ambientlight.h"
#include "engine/rendering/material.h"
#include "engine/rendering/renderingengine.h"
#include "engine/rendering/shaders/shader.h"
#include "engine/core/transform.h"
#include "engine/math/vector3.h"

namespace SGE
{

AmbientShader::AmbientShader()
    : Shader{"res/shaders/ambient_light_vertex.glsl",
             "res/shaders/ambient_light_fragment.glsl"}
{
}

void AmbientShader::update_uniforms(
    const Transform& transform, const Material& material,
    const RenderingEngine& rendering_engine) const
{
    set_uniform("transform_u", transform.get_transformation());

    set_uniform("material_u.shininess", material.shininess());

    // auto* light =
    // dynamic_cast<AmbientLight*>(rendering_engine.active_light()); if (light
    // == nullptr) {
    //    throw std::runtime_error{"An ambient light has malfunctioned."};
    //}

    // set_uniform("intensity_u", Vector3{light->intensity(),
    // light->intensity(),
    //                                   light->intensity()});
}

} // namespace SGE
