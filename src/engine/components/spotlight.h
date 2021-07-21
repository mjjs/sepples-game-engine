#ifndef _SGE_SPOTLIGHT_H
#define _SGE_SPOTLIGHT_H

#include "light.h"
#include "vector3.h"

#include <memory>

namespace SGE {
class SpotLight : public SGE::Light {
    private:
        Math::Vector3 direction_{};

        float cut_off_ = 0;
        float outer_cut_off_ = 0;

        float constant_ = 0;
        float linear_ = 0;
        float quadratic_ = 0;

    public:
        SpotLight();
        explicit SpotLight(
                const Math::Vector3& direction,
                const Math::Vector3& colour,
                float intensity,
                float cut_off,
                float outer_cut_off,
                float constant,
                float linear,
                float quadratic
                );

        inline const Math::Vector3& direction() const
        {
            return direction_;
        }

        inline float cut_off() const
        {
            return cut_off_;
        }

        inline float outer_cut_off() const
        {
            return outer_cut_off_;
        }

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
