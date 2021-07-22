#include "ambientlight.h"
#include "ambientshader.h"
#include "light.h"
#include "renderingengine.h"
#include "vector3.h"

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
