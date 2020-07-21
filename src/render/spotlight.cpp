#include "spotlight.h"
#include "vector3.h"

SpotLight::SpotLight(
                const Math::Vector3& position,
                const Math::Vector3& direction,
                const Math::Vector3& colour,
                float intensity,
                float cut_off,
                float outer_cut_off,
                float constant,
                float linear,
                float quadratic
                ) :
    position{position},
    direction{direction},
    colour{colour},
    intensity{intensity},
    cut_off{cut_off},
    outer_cut_off{outer_cut_off},
    constant{constant},
    linear{linear},
    quadratic{quadratic}
{}
