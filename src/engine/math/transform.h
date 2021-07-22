#ifndef _SGE_TRANSFORM_H
#define _SGE_TRANSFORM_H

#include "camera.h"
#include "matrix4.h"
#include "vector3.h"
#include "quaternion.h"

namespace SGE {

class Transform {
    private:
        Vector3 position_;
        Quaternion rotation_;
        Vector3 scale_{1,1,1};

    public:
        inline void set_position(const Vector3& position_vector)
        {
            position_ = position_vector;
        }

        inline const Vector3& position() const
        {
            return position_;
        }

        inline void set_rotation(const Quaternion& rotation)
        {
            rotation_ = rotation;
        }

        inline Quaternion rotation() const
        {
            return rotation_;
        }

        inline void set_scale(const Vector3& scale_vector)
        {
            scale_ = scale_vector;
        }

        inline Matrix4 get_projected_transformation(const Camera& camera) const
        {
            return camera.get_view_projection() * get_transformation();
        }

        Matrix4 get_transformation() const;
};

} // namespace SGE
#endif
