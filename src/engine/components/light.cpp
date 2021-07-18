#include "light.h"
#include "renderingengine.h"
#include "shader.h"
#include "vector3.h"

#include <memory>

SGE::Light::Light(std::shared_ptr<Shader> shader)
    : shader_{shader}
{
}

SGE::Light::Light(
    std::shared_ptr<Shader> shader,
    const Math::Vector3& colour,
    float intensity
) : 
    colour_{colour},
    intensity_{intensity},
    shader_{shader}
{
}

float SGE::Light::intensity() const
{
    return intensity_;
}

const Math::Vector3& SGE::Light::colour() const
{
    return colour_;
}

std::shared_ptr<Shader> SGE::Light::shader() const
{
    return shader_;
}

void SGE::Light::add_to_rendering_engine(SGE::RenderingEngine& rendering_engine)
{
    rendering_engine.add_light(this);
}
