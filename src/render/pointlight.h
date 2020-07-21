#ifndef _SGE_POINTLIGHT_H
#define _SGE_POINTLIGHT_H

#include "vector3.h"

struct PointLight {
    Math::Vector3 position;
    Math::Vector3 colour;

    float intensity;

    float constant;
    float linear;
    float quadratic;

    PointLight() = default;
    explicit PointLight(
            const Math::Vector3& position,
            const Math::Vector3& colour,
            float intensity,
            float constant,
            float linear,
            float quadratic
            );
};
#endif
