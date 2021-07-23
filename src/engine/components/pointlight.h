#ifndef _SGE_POINTLIGHT_H
#define _SGE_POINTLIGHT_H

#include "light.h"
#include "vector3.h"

namespace SGE {
class PointLight : public Light {
    private:
        float constant_ = 0;
        float linear_ = 0;
        float quadratic_ = 0;

    public:
        PointLight();
        explicit PointLight(
                const Vector3& colour,
                float intensity,
                float constant,
                float linear,
                float quadratic
                );

        const Vector3& position() const;
        float constant() const;
        float linear() const;
        float quadratic() const;
};
} // namespace SGE
#endif
