#ifndef _SGE_SPOTLIGHT_H
#define _SGE_SPOTLIGHT_H

#include "light.h"
#include "vector3.h"

#include <memory>

namespace SGE {
class SpotLight : public SGE::Light {
    private:
        Math::Vector3 position_{};
        Math::Vector3 direction_{};

        float cut_off_ = 0;
        float outer_cut_off_ = 0;

        float constant_ = 0;
        float linear_ = 0;
        float quadratic_ = 0;

    public:
        SpotLight();
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

        const Math::Vector3& position() const;
        const Math::Vector3& direction() const;

        float cut_off() const;
        float outer_cut_off() const;

        float constant() const;
        float linear() const;
        float quadratic() const;

};
} // namespace SGE
#endif
