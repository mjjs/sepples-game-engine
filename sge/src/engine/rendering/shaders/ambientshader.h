#ifndef _SGE_AMBIENTSHADER_H
#define _SGE_AMBIENTSHADER_H
#include "engine/rendering/material.h"
#include "engine/rendering/shaders/shader.h"
#include "engine/core/transform.h"
#include "engine/math/vector3.h"

namespace SGE
{

class AmbientShader : public Shader
{
  public:
    AmbientShader();
    void update_uniforms(
        const Transform& transform, const Material& material,
        const SGE::RenderingEngine& rendering_engine) const override;
};

} // namespace SGE

#endif
