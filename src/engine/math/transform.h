#ifndef _SGE_TRANSFORM_H
#define _SGE_TRANSFORM_H

#include "camera.h"
#include "matrix4.h"
#include "vector3.h"

namespace SGE {
namespace Math {

class Transform {
    private:
        Vector3 position_;
        Vector3 rotation_;
        Vector3 scale_{1,1,1};

    public:
        void set_position(const Vector3& position_vector);
        Vector3& position();
        void set_rotation(const Vector3& rotation_vector);
        void set_scale(const Vector3& scale_vector);
        Matrix4 get_transformation() const;
        Matrix4 get_projected_transformation(const Camera& camera) const;
};

} // namespace Math
} // namespace SGE
#endif
