#include "ambientshader.h"

#include "ambientlight.h"
#include "material.h"
#include "renderingengine.h"
#include "shader.h"
#include "transform.h"
#include "vector3.h"

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
