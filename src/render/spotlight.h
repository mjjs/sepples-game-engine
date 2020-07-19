#ifndef _SGE_SPOTLIGHT_H
#define _SGE_SPOTLIGHT_H

#include "vector3.h"

struct SpotLight{
    Math::Vector3 position{};
    Math::Vector3 direction{};
    Math::Vector3 colour{};

    float cut_off = 0.0;
    float outer_cut_off = 0.0;

    float constant = 1.0;
    float linear = 0.0;
    float quadratic = 0.0;
};
#endif
