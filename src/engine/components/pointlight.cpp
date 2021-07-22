#include "light.h"
#include "pointlight.h"
#include "pointshader.h"
#include "vector3.h"

#include <memory>

namespace SGE {

PointLight::PointLight()
    : Light{std::make_shared<PointShader>()}
{
}

PointLight::PointLight(
        const Vector3& colour,
        float intensity,
        float constant,
        float linear,
        float quadratic
        ) :
    Light{std::make_shared<PointShader>(), colour, intensity},
    constant_{constant},
    linear_{linear},
    quadratic_{quadratic}
{}

} // namespace SGE
