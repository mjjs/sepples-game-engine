#ifndef _SGE_PHONGSHADER_H
#define _SGE_PHONGSHADER_H
#include "shader.h"
#include "vector3.h"

class PhongShader : public Shader {
    private:
        Math::Vector3 ambient_light_strength_;

    public:
        PhongShader();
        void set_ambient_light_strength(const Math::Vector3& light);
};

#endif
