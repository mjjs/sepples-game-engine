#include "engine/ecs/components/transformcomponent.h"

#include "engine/core/transform.h"

namespace SGE
{

TransformComponent::TransformComponent(const Transform& transform)
    : transform_{transform}
{
}

const Transform& TransformComponent::transform() const
{
    return transform_;
}

Transform& TransformComponent::transform()
{
    return transform_;
}

} // namespace SGE
