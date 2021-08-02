#ifndef _SGE_AMBIENTLIGHT_H
#define _SGE_AMBIENTLIGHT_H

#include "light.h"
#include "vector3.h"

namespace SGE {
class AmbientLight : public Light {
    private:
        Vector3 direction_;

    public:
        AmbientLight();
        explicit AmbientLight(float intensity);
};
} // namespace SGE

#endif
