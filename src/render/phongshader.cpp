#include "phongshader.h"
#include "shader.h"

PhongShader::PhongShader() :
    Shader{"res/shaders/phong_vertex.glsl", "res/shaders/phong_fragment.glsl"}
{
    add_uniform("ambient_light_strength");
}

void PhongShader::set_ambient_light_strength(const Math::Vector3& light)
{
    ambient_light_strength_ = light;
    set_uniform("ambient_light_strength", light);
}
