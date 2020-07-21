#include "directionallight.h"
#include "vector3.h"


DirectionalLight::DirectionalLight(const Math::Vector3& direction, const Math::Vector3& colour, float intensity) :
    direction{direction},
    colour{colour},
    intensity{intensity}
{}
