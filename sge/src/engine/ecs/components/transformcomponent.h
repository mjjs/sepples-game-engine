#ifndef _SGE_TRANSFORM_COMPONENT_H
#define _SGE_TRANSFORM_COMPONENT_H

#include "engine/core/transform.h"

namespace SGE
{

class TransformComponent
{
  private:
    Transform transform_;

  public:
    TransformComponent() = default;
    TransformComponent(const Transform& transform);

    const Transform& transform() const;
    Transform& transform();
};

} // namespace SGE
#endif
