#ifndef _SGE_DIRECTIONALSHADER_H
#define _SGE_DIRECTIONALSHADER_H

#include "shader.h"
#include "vector3.h"

namespace SGE
{

class DirectionalShader : public Shader
{
  public:
    DirectionalShader();

    void update_uniforms(
        const Transform& transform, const Material& material,
        const SGE::RenderingEngine& rendering_engine) const override;
};

} // namespace SGE
#endif
