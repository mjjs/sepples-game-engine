#include "phongshader.h"
#include "shader.h"

PhongShader::PhongShader() :
    Shader{"res/shaders/phong_vertex.glsl", "res/shaders/phong_fragment.glsl"}
{
    add_uniform("ambient_light_strength");
    add_uniform("diffuse_light_position");
    add_uniform("view_position");
}

void PhongShader::set_ambient_light_strength(const Math::Vector3& light)
{
    ambient_light_strength_ = light;
    set_uniform("ambient_light_strength", light);
}

void PhongShader::set_diffuse_light_position(const Math::Vector3& light)
{
    diffuse_light_position_ = light;
    set_uniform("diffuse_light_position", light);
}

void PhongShader::set_view_position(const Math::Vector3& position)
{
    set_uniform("view_position", position);
}
