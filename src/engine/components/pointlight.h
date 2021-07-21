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
                const Math::Vector3& colour,
                float intensity,
                float constant,
                float linear,
                float quadratic
                );

        const Math::Vector3& position() const;
        inline float constant() const
        {
            return constant_;
        }

        inline float linear() const
        {
            return linear_;
        }

        inline float quadratic() const
        {
            return quadratic_;
        }
};
} // namespace SGE
#endif
