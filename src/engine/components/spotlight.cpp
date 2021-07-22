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

} // namespace SGE
