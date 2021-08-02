#include "directionallight.h"
#include "directionalshader.h"
#include "light.h"
#include "vector3.h"
#include "renderingengine.h"

#include <memory>

namespace SGE {

DirectionalLight::DirectionalLight()
    : Light(std::make_shared<DirectionalShader>())
{
}

DirectionalLight::DirectionalLight(
        const Vector3& colour,
        float intensity
        ) :
    Light(std::make_shared<DirectionalShader>(), colour, intensity)
{
}

Vector3 DirectionalLight::direction() const
{
    return get_transform().rotation().get_forward();
}

} // namespace SGE
