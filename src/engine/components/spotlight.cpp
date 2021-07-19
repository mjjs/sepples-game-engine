#include "light.h"
#include "spotshader.h"
#include "spotlight.h"
#include "vector3.h"

#include <memory>

SGE::SpotLight::SpotLight()
    : Light{std::make_shared<SpotShader>()}
{
}

SGE::SpotLight::SpotLight(
                const Math::Vector3& direction,
                const Math::Vector3& colour,
                float intensity,
                float cut_off,
                float outer_cut_off,
                float constant,
                float linear,
                float quadratic
                ) :
    Light{std::make_shared<SpotShader>(), colour, intensity},
    direction_{direction},
    cut_off_{cut_off},
    outer_cut_off_{outer_cut_off},
    constant_{constant},
    linear_{linear},
    quadratic_{quadratic}
{
}

const Math::Vector3& SGE::SpotLight::direction() const
{
    return direction_;
}

float SGE::SpotLight::cut_off() const
{
    return cut_off_;
}

float SGE::SpotLight::outer_cut_off() const
{
    return outer_cut_off_;
}

float SGE::SpotLight::constant() const
{
    return constant_;
}

float SGE::SpotLight::linear() const
{
    return linear_;
}

float SGE::SpotLight::quadratic() const
{
    return quadratic_;
}
