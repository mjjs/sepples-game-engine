#ifndef _SGE_SPOTLIGHT_H
#define _SGE_SPOTLIGHT_H

#include "vector3.h"

struct SpotLight{
    Math::Vector3 position;
    Math::Vector3 direction;
    Math::Vector3 colour;

    float intensity;

    float cut_off;
    float outer_cut_off;

    float constant;
    float linear;
    float quadratic;

    SpotLight() = default;
    explicit SpotLight(
            const Math::Vector3& position,
            const Math::Vector3& direction,
            const Math::Vector3& colour,
            float intensity,
            float cut_off,
            float outer_cut_off,
            float constant,
            float linear,
            float quadratic
            );
};
#endif
