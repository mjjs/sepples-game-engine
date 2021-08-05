#ifndef _SGE_SPOTSHADER_H
#define _SGE_SPOTSHADER_H
#include "engine/rendering/shaders/shader.h"
#include "engine/math/vector3.h"

namespace SGE
{

class SpotShader : public Shader
{
  public:
    SpotShader();

    void
    update_uniforms(const Transform& transform, const Material& material,
                    const RenderingEngine& rendering_engine) const override;
};

} // namespace SGE

#endif
