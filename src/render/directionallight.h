#ifndef _SGE_DIRECTIONALLIGHT_H
#define _SGE_DIRECTIONALLIGHT_H

#include "vector3.h"

struct DirectionalLight {
    Math::Vector3 direction;
    Math::Vector3 colour;
    float intensity;

    DirectionalLight() = default;
    explicit DirectionalLight(const Math::Vector3& direction, const Math::Vector3& colour, float intensity);
};

#endif
