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
        Math::Vector3 direction_;

    public:
        DirectionalLight();
        explicit DirectionalLight(
            const Math::Vector3& direction,
            const Math::Vector3& colour,
            float intensity
        );

        inline const Math::Vector3& direction() const
        {
            return direction_;
        }
};
} // namespace SGE

#endif
