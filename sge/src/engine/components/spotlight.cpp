#include "light.h"
#include "spotshader.h"
#include "spotlight.h"
#include "vector3.h"

#include <memory>

namespace SGE {

SpotLight::SpotLight()
    : Light{std::make_shared<SpotShader>()}
{
}

SpotLight::SpotLight(
                const Vector3& colour,
                float intensity,
                float cut_off,
                float outer_cut_off,
                float constant,
                float linear,
                float quadratic
                ) :
    Light{std::make_shared<SpotShader>(), colour, intensity},
    cut_off_{cut_off},
    outer_cut_off_{outer_cut_off},
    constant_{constant},
    linear_{linear},
    quadratic_{quadratic}
{
}

Vector3 SpotLight::direction() const
{
    return get_transform().rotation().get_forward();
}

float SpotLight::cut_off() const
{
    return cut_off_;
}

float SpotLight::outer_cut_off() const
{
    return outer_cut_off_;
}

float SpotLight::constant() const
{
    return constant_;
}

float SpotLight::linear() const
{
    return linear_;
}

float SpotLight::quadratic() const
{
    return quadratic_;
}

} // namespace SGE
