#ifndef _SGE_CAMERA_H
#define _SGE_CAMERA_H

#include "engine/core/transform.h"

#include <glm/glm.hpp>

namespace SGE
{

class Camera
{
    enum class ProjectionType {
        PERSPECTIVE,
        ORTHOGRAPHIC,
    };

  private:
    float z_near_{0};
    float z_far_{0};

    // Perspective camera
    float fov_degrees_{0};
    float aspect_ratio_{0};

    // Orthographic camera
    float left_{0};
    float right_{0};
    float bottom_{0};
    float top_{0};

    ProjectionType projection_type_;

    glm::mat4 projection_{1.0F};
    Transform transform_;

  public:
    constexpr static const glm::vec3 world_up_{0.0F, 1.0F, 0.0F};

    // Perspective constructor
    Camera(float fov_degrees, float aspect_ratio, float z_near, float z_far);

    // Orthographic constructor
    Camera(float left, float right, float bottom, float top, float z_near,
           float z_far);

    void move(const glm::vec3& direction, float amount);
    void rotate_x(float degrees);
    void rotate_y(float degrees);

    void update_aspect_ratio(unsigned int width, unsigned int height);

    glm::mat4 get_view_projection() const;

    const Transform& transform() const;
};

} // namespace SGE
#endif
