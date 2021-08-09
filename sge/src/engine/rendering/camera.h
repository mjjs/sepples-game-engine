#ifndef _SGE_CAMERA_H
#define _SGE_CAMERA_H

#include "engine/core/transform.h"
#include "engine/math/matrix4.h"
#include "engine/math/sgemath.h"
#include "engine/math/vector3.h"

namespace SGE
{

class RenderingEngine;

class Camera
{
  private:
    Matrix4 projection_;
    Transform transform_;

  public:
    constexpr static const Vector3 world_up_{0, 1, 0};

    Camera(float fov_degrees, float aspect_ratio, float z_near, float z_far);

    void move(const Vector3& direction, float amount);
    void rotate_x(float degrees);
    void rotate_y(float degrees);

    Matrix4 get_view_projection() const;

    const Transform& transform() const;
};

} // namespace SGE
#endif