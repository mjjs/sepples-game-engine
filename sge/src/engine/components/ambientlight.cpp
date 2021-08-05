#include "engine/components/ambientlight.h"
#include "engine/rendering/shaders/ambientshader.h"
#include "engine/components/light.h"
#include "engine/rendering/renderingengine.h"
#include "engine/math/vector3.h"

#include <memory>

SGE::AmbientLight::AmbientLight()
    : Light(std::make_shared<AmbientShader>())
{
}

SGE::AmbientLight::AmbientLight(float intensity) :
    Light(
            std::make_shared<AmbientShader>(),
            Vector3{1.0F, 1.0F, 1.0F},
            intensity
         )
{
}
