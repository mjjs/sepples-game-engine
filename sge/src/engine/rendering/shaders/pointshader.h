#ifndef _SGE_POINTSHADER_H
#define _SGE_POINTSHADER_H
#include "engine/rendering/shaders/shader.h"
#include "engine/math/vector3.h"

namespace SGE
{

class PointShader : public Shader
{
  public:
    PointShader();

    void update_uniforms(
        const Transform& transform, const Material& material,
        const SGE::RenderingEngine& rendering_engine) const override;
};

} // namespace SGE
#endif
