#ifndef _SGE_AMBIENTSHADER_H
#define _SGE_AMBIENTSHADER_H
#include "material.h"
#include "transform.h"
#include "shader.h"
#include "vector3.h"

class AmbientShader : public Shader {
    public:
        AmbientShader();
        void update_uniforms(
                const Math::Transform& transform,
                const Material& material,
                const SGE::RenderingEngine& rendering_engine) override;
};

#endif