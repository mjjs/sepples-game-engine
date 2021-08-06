#ifndef _SGE_CAMERA_COMPONENT_H
#define _SGE_CAMERA_COMPONENT_H

#include "engine/rendering/camera.h"

namespace SGE
{

class CameraComponent
{
  private:
    Camera camera_;

  public:
    CameraComponent();
    CameraComponent(const Camera& camera);

    const Camera& camera() const;
    Camera& camera();
};

} // namespace SGE

#endif
