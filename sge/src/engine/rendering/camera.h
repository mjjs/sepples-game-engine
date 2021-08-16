#ifndef _SGE_CAMERA_H
#define _SGE_CAMERA_H

#include "engine/core/transform.h"

#include <glm/glm.hpp>

namespace SGE
{

class Camera
{
  private:
    float fov_degrees_;
    float aspect_ratio_;
    float z_near_;
    float z_far_;

    glm::mat4 projection_;
    Transform transform_;

  public:
    constexpr static const glm::vec3 world_up_{0, 1, 0};

    Camera(float fov_degrees, float aspect_ratio, float z_near, float z_far);

    void move(const glm::vec3& direction, float amount);
    void rotate_x(float degrees);
    void rotate_y(float degrees);

    void update_aspect_ratio(unsigned int width, unsigned int height);

    glm::mat4 get_view_projection() const;

    const Transform& transform() const;
};

} // namespace SGE
#endif
