#ifndef _SGE_SPOTSHADER_H
#define _SGE_SPOTSHADER_H
#include "shader.h"
#include "vector3.h"

class SpotShader : public Shader {
    public:
        SpotShader();

        void update_uniforms(
                const Math::Transform& transform,
                const Material& material,
                const SGE::RenderingEngine& rendering_engine) override;
};

#endif
