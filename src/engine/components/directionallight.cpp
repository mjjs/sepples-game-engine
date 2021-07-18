#include "directionallight.h"
#include "directionalshader.h"
#include "light.h"
#include "vector3.h"
#include "renderingengine.h"

#include <memory>
#include <iostream>

SGE::DirectionalLight::DirectionalLight()
    : Light(std::make_shared<DirectionalShader>())
{
}

SGE::DirectionalLight::DirectionalLight(
        const Math::Vector3& direction,
        const Math::Vector3& colour,
        float intensity
        ) :
    Light(std::make_shared<DirectionalShader>(), colour, intensity),
    direction_{direction}
{
}

const Math::Vector3& SGE::DirectionalLight::direction() const
{
    return direction_;
}
