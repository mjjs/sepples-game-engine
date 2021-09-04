#ifndef _SGE_CAMERA_H
#define _SGE_CAMERA_H

#include <glm/glm.hpp>

namespace SGE
{

class Camera
{
  public:
    enum class ProjectionType {
        PERSPECTIVE,
        ORTHOGRAPHIC,
    };

  private:
    // Perspective camera
    float fov_degrees_{75.0F};
    float aspect_ratio_{0};
    float perspective_z_near_{0.01F};
    float perspective_z_far_{1000.0F};

    // Orthographic camera
    float orthographic_size_{10.0F};
    float orthographic_z_near_{-1.0F};
    float orthographic_z_far_{1.0F};

    ProjectionType projection_type_{ProjectionType::PERSPECTIVE};

    glm::mat4 projection_{1.0F};

    bool primary_{true};

    void recalculate_projection();

  public:
    constexpr static const glm::vec3 world_up_{0.0F, 1.0F, 0.0F};

    void set_orthographic(float size, float z_near, float z_far);
    void set_perspective(float fov_degrees, float z_near, float z_far);

    void update_aspect_ratio(unsigned int width, unsigned int height);

    const glm::mat4& projection() const
    {
        return projection_;
    }

    ProjectionType projection_type() const
    {
        return projection_type_;
    }

    void set_projection_type(ProjectionType projection_type)
    {
        projection_type_ = projection_type;
        recalculate_projection();
    }

    // Perspective
    float fov() const
    {
        return fov_degrees_;
    }

    void set_fov(const float degrees)
    {
        fov_degrees_ = degrees;
        recalculate_projection();
    }

    float aspect_ratio() const
    {
        return aspect_ratio_;
    }

    void set_aspect_ratio(const float aspect_ratio)
    {
        aspect_ratio_ = aspect_ratio;
        recalculate_projection();
    }

    float perspective_z_near() const
    {
        return perspective_z_near_;
    }

    void set_perspective_z_near(const float z_near)
    {
        perspective_z_near_ = z_near;
        recalculate_projection();
    }

    float perspective_z_far() const
    {
        return perspective_z_far_;
    }

    void set_perspective_z_far(const float z_far)
    {
        perspective_z_far_ = z_far;
        recalculate_projection();
    }

    // Orghographic
    // float size, float z_near, float z_far
    float orthographic_size() const
    {
        return orthographic_size_;
    }

    void set_orthographic_size(const float orthographic_size)
    {
        orthographic_size_ = orthographic_size;
        recalculate_projection();
    }

    float orthographic_z_near() const
    {
        return orthographic_z_near_;
    }

    void set_orthographic_z_near(const float z_near)
    {
        orthographic_z_near_ = z_near;
        recalculate_projection();
    }

    float orthographic_z_far() const
    {
        return orthographic_z_far_;
    }

    void set_orthographic_z_far(const float z_far)
    {
        orthographic_z_far_ = z_far;
        recalculate_projection();
    }

    bool primary() const
    {
        return primary_;
    }

    void set_primary(bool primary)
    {
        primary_ = primary;
    }
};

} // namespace SGE
#endif
