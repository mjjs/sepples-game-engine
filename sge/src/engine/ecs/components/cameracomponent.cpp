#include "engine/ecs/components/cameracomponent.h"

#include "engine/rendering/camera.h"

namespace SGE
{

CameraComponent::CameraComponent()
    // Ortho
    //: camera_{0, 1270, 0, 800, -1, 1}
    // Perspective
    : camera_{70, (float)1270 / (float)800, .1, 100}
{
}

CameraComponent::CameraComponent(const Camera& camera) : camera_{camera}
{
}

const Camera& CameraComponent::camera() const
{
    return camera_;
}

Camera& CameraComponent::camera()
{
    return camera_;
}

} // namespace SGE
