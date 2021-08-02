#ifndef _SGE_CAMERA_H
#define _SGE_CAMERA_H

#include "gamecomponent.h"
#include "matrix4.h"
#include "sgemath.h"
#include "vector3.h"

namespace SGE {
class RenderingEngine;

class Camera : public GameComponent {
    private:
        Matrix4 projection_;

    public:
        constexpr static const Vector3 world_up_{0,1,0};

        Camera(float fov_radians, float aspect_ratio, float z_near, float z_far);

        void move(const Vector3& direction, float amount);
        void rotate_x(float degrees);
        void rotate_y(float degrees);

        Matrix4 get_view_projection() const;

        void add_to_rendering_engine(RenderingEngine& rendering_engine) override;
        void update(float delta) override;
};

} // namespace SGE
#endif
