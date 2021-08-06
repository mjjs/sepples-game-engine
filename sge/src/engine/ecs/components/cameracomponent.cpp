#include "engine/ecs/components/cameracomponent.h"

#include "engine/rendering/camera.h"

namespace SGE
{

CameraComponent::CameraComponent()
    : camera_{70, (float)1270 / (float)800, .1, 1000}
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
