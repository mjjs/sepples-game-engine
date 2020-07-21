#include "pointlight.h"
#include "vector3.h"

PointLight::PointLight(
        const Math::Vector3& position,
        const Math::Vector3& colour,
        float intensity,
        float constant,
        float linear,
        float quadratic
        ) :
    position{position},
    colour{colour},
    intensity{intensity},
    constant{constant},
    linear{linear},
    quadratic{quadratic}
{}
