#ifndef _SGE_DIRECTIONALSAHDER_H
#define _SGE_DIRECTIONALSAHDER_H
#include "shader.h"
#include "vector3.h"

class DirectionalShader : public Shader {
    private:
        Math::Vector3 ambient_light_strength_;
        Math::Vector3 diffuse_light_position_;

    public:
        DirectionalShader();

        void update_uniforms(
                const Math::Transform& transform,
                const Material& material,
                const SGE::RenderingEngine& rendering_engine) override;

        void set_view_position(const Math::Vector3& position);
};

#endif
