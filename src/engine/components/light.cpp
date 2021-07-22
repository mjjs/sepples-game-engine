#include "light.h"
#include "renderingengine.h"
#include "shader.h"
#include "vector3.h"

#include <memory>

namespace SGE {

Light::Light(std::shared_ptr<Shader> shader)
    : shader_{shader}
{
}

Light::Light(
    std::shared_ptr<Shader> shader,
    const Vector3& colour,
    float intensity
) : 
    colour_{colour},
    intensity_{intensity},
    shader_{shader}
{
}

void Light::add_to_rendering_engine(RenderingEngine& rendering_engine)
{
    rendering_engine.add_light(this);
}

} // namespace SGE
