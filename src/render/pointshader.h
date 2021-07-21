#ifndef _SGE_POINTSHADER_H
#define _SGE_POINTSHADER_H
#include "shader.h"
#include "vector3.h"

namespace SGE {

class PointShader : public Shader {
    public:
        PointShader();

        void update_uniforms(
                const Math::Transform& transform,
                const Material& material,
                const SGE::RenderingEngine& rendering_engine) override;
};

} // namespace SGE
#endif
