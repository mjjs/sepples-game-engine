#ifndef _SGE_POINTLIGHT_H
#define _SGE_POINTLIGHT_H

#include "vector3.h"

struct PointLight {
    Math::Vector3 position{};
    Math::Vector3 colour{};

    float constant = 1.0F;
    float linear = 0.0F;
    float quadratic = 0.0F;
};
#endif
