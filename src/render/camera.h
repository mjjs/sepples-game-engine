#ifndef _SGE_CAMERA_H
#define _SGE_CAMERA_H

#include "matrix4.h"
#include "sgemath.h"
#include "vector3.h"

namespace SGE {

class Camera {
    private:
        Vector3 position_;
        Vector3 forward_;
        Vector3 up_;
        Matrix4 projection_;

    public:
        static inline const Vector3 world_up_{0,1,0};

        Camera(float fov_radians, float aspect_ratio, float z_near, float z_far);

        inline void move(const Vector3& direction, float amount)
        {
            position_ = position_ + amount * direction;
        }

        void rotate_x(float radians);
        void rotate_y(float radians);

        Matrix4 get_view_projection() const;

        inline Vector3 get_position() const
        {
            return position_;
        }

        inline Vector3 get_left() const
        {
            return normalize(cross(forward_, up_));
        }

        inline Vector3 get_right() const
        {
            return normalize(cross(up_, forward_));
        }

        inline Vector3 get_forward() const
        {
            return forward_;
        }

        inline Vector3 get_up() const
        {
            return up_;
        }
};

} // namespace SGE
#endif
