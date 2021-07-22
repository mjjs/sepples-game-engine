#ifndef _SGE_DIRECTIONALLIGHT_H
#define _SGE_DIRECTIONALLIGHT_H

#include "gamecomponent.h"
#include "light.h"
#include "shader.h"
#include "vector3.h"

#include <memory>

namespace SGE {
class DirectionalLight : public Light {
    private:
        Vector3 direction_;

    public:
        DirectionalLight();
        explicit DirectionalLight(
            const Vector3& direction,
            const Vector3& colour,
            float intensity
        );

        inline const Vector3& direction() const
        {
            return direction_;
        }
};
} // namespace SGE

#endif
