#include "engine/components/light.h"
#include "engine/components/pointlight.h"
#include "engine/rendering/shaders/pointshader.h"
#include "engine/math/vector3.h"

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

float PointLight::constant() const
{
    return constant_;
}

float PointLight::linear() const
{
    return linear_;
}

float PointLight::quadratic() const
{
    return quadratic_;
}

} // namespace SGE
