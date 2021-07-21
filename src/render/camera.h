#ifndef _SGE_CAMERA_H
#define _SGE_CAMERA_H

#include "matrix4.h"
#include "sgemath.h"
#include "vector3.h"

namespace SGE {

class Camera {
    private:
        Math::Vector3 position_;
        Math::Vector3 forward_;
        Math::Vector3 up_;
        Math::Matrix4 projection_;

    public:
        static inline const Math::Vector3 world_up_{0,1,0};

        Camera(float fov_radians, float aspect_ratio, float z_near, float z_far);

        inline void move(const Math::Vector3& direction, float amount)
        {
            position_ = position_ + amount * direction;
        }

        void rotate_x(float degrees);
        void rotate_y(float degrees);

        Math::Matrix4 get_view_projection() const;

        inline Math::Vector3 get_position() const
        {
            return position_;
        }

        inline Math::Vector3 get_left() const
        {
            return Math::normalize(Math::cross(forward_, up_));
        }

        inline Math::Vector3 get_right() const
        {
            return Math::normalize(Math::cross(up_, forward_));
        }

        inline Math::Vector3 get_forward() const
        {
            return forward_;
        }

        inline Math::Vector3 get_up() const
        {
            return up_;
        }
};

} // namespace SGE
#endif
