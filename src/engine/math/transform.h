#ifndef _SGE_TRANSFORM_H
#define _SGE_TRANSFORM_H

#include "matrix4.h"
#include "vector3.h"
#include "quaternion.h"

namespace SGE {
class Camera;

class Transform {
    private:
        Vector3 position_;
        Quaternion rotation_;
        Vector3 scale_{1,1,1};

    public:
        void set_position(const Vector3& position_vector);
        const Vector3& position() const;
        void set_rotation(const Quaternion& rotation);
        Quaternion rotation() const;
        void set_scale(const Vector3& scale_vector);
        Matrix4 get_projected_transformation(const Camera& camera) const;
        Matrix4 get_transformation() const;
};

} // namespace SGE
#endif
