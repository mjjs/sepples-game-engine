#ifndef _SGE_CAMERA_H
#define _SGE_CAMERA_H

#include "vector3.h"
#include "matrix4.h"

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

        void move(const Math::Vector3& direction, float amount);
        void rotate_x(float degrees);
        void rotate_y(float degrees);

        Math::Matrix4 get_view_projection() const;
        Math::Vector3 get_position() const;
        Math::Vector3 get_left() const;
        Math::Vector3 get_right() const;
        Math::Vector3 get_forward() const;
        Math::Vector3 get_up() const;
};

} // namespace SGE
#endif
