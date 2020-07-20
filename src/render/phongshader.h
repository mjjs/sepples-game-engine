#ifndef _SGE_PHONGSHADER_H
#define _SGE_PHONGSHADER_H
#include "directionallight.h"
#include "pointlight.h"
#include "shader.h"
#include "spotlight.h"
#include "vector3.h"

class PhongShader : public Shader {
    private:
        Math::Vector3 ambient_light_strength_;
        Math::Vector3 diffuse_light_position_;

    public:
        using Shader::set_uniform;

        PhongShader();
        void set_view_position(const Math::Vector3& position);
        void set_uniform(const SpotLight& light);
        void set_uniform(const DirectionalLight& light);
        void set_uniform(const PointLight& light);
};

#endif
