#ifndef _SGE_PHONGSHADER_H
#define _SGE_PHONGSHADER_H
#include "shader.h"
#include "vector3.h"

class PhongShader : public Shader {
    private:
        Math::Vector3 ambient_light_strength_;
        Math::Vector3 diffuse_light_position_;

    public:
        PhongShader();
        void set_ambient_light_strength(const Math::Vector3& light);
        void set_diffuse_light_position(const Math::Vector3& light);
        void set_view_position(const Math::Vector3& position);
};

#endif
