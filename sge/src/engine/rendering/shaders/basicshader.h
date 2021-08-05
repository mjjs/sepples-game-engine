#ifndef _SGE_BASICSHADER_H
#define _SGE_BASICSHADER_H
#include "engine/rendering/material.h"
#include "engine/rendering/shaders/shader.h"
#include "engine/core/transform.h"

namespace SGE
{

class BasicShader : public Shader
{
  public:
    BasicShader();
    void update_uniforms(
        const Transform& transformation, const Material& material,
        const SGE::RenderingEngine& rendering_engine) const override;
};

} // namespace SGE

#endif