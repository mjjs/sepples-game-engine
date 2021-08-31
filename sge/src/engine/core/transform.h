#ifndef _SGE_TRANSFORM_H
#define _SGE_TRANSFORM_H

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

namespace SGE
{
class Camera;
class GameObject;

class Transform
{
    friend class GameObject;

  private:
    glm::vec3 position_{};
    glm::quat rotation_{1.0F, 0.0F, 0.0F, 0.0F};
    glm::vec3 scale_{1.0F};

    glm::vec3 rotation_euler_hints_{0.0F};

  public:
    enum class RotationSpace { SELF, WORLD };

    void set_position(const glm::vec3& position_vector)
    {
        position_ = position_vector;
    }

    const glm::vec3& position() const
    {
        return position_;
    }

    glm::vec3& position()
    {
        return position_;
    }

    glm::vec3& rotation_euler_hints()
    {
        return rotation_euler_hints_;
    }

    void set_rotation(const glm::quat& rotation)
    {
        rotation_ = rotation;
    }

    void set_rotation(const glm::vec3& euler_angles,
                      RotationSpace relative_to = RotationSpace::SELF);

    glm::quat rotation() const
    {
        return rotation_;
    }

    void set_scale(const glm::vec3& scale_vector)
    {
        scale_ = scale_vector;
    }

    glm::vec3& scale()
    {
        return scale_;
    }

    glm::mat4 get_transformation() const;

    void rotate(const glm::vec3& euler_angles,
                RotationSpace relative_to = RotationSpace::SELF);
};

} // namespace SGE
#endif
