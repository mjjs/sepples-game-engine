#ifndef _SGE_BASICSHADER_H
#define _SGE_BASICSHADER_H
#include "shader.h"
#include "material.h"
#include "transform.h"

class BasicShader : public Shader {
    public:
        BasicShader();
        void update_uniforms(
                const Math::Transform& transformation,
                const Material& material,
                const SGE::RenderingEngine& rendering_engine) override;
};

#endif
