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
    Transform* parent_ = nullptr;

    glm::vec3 position_;
    glm::quat rotation_{0, 0, 0, 1};
    glm::vec3 scale_{1.0F, 1.0F, 1.0F};

    void set_parent(Transform* transform);

  public:
    void set_position(const glm::vec3& position_vector);
    const glm::vec3& position() const;
    void set_rotation(const glm::quat& rotation);
    glm::quat rotation() const;
    void set_scale(const glm::vec3& scale_vector);
    glm::mat4 get_projected_transformation(const Camera& camera) const;
    glm::mat4 get_transformation() const;
};

} // namespace SGE
#endif
