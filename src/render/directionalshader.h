#ifndef _SGE_DIRECTIONALSAHDER_H
#define _SGE_DIRECTIONALSAHDER_H
#include "shader.h"
#include "vector3.h"

class DirectionalShader : public Shader {
    public:
        DirectionalShader();

        void update_uniforms(
                const Math::Transform& transform,
                const Material& material,
                const SGE::RenderingEngine& rendering_engine) override;
};

#endif
