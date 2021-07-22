#ifndef _SGE_DIRECTIONALLIGHT_H
#define _SGE_DIRECTIONALLIGHT_H

#include "gamecomponent.h"
#include "light.h"
#include "shader.h"
#include "vector3.h"

#include <memory>

namespace SGE {
class DirectionalLight : public Light {
    public:
        DirectionalLight();
        explicit DirectionalLight(
            const Vector3& colour,
            float intensity
        );

        inline Vector3 direction() const
        {
            return get_transform().rotation().get_forward();
        }
};
} // namespace SGE

#endif
