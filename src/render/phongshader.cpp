#include "directionallight.h"
#include "phongshader.h"
#include "pointlight.h"
#include "spotlight.h"
#include "shader.h"
#include "vector3.h"

PhongShader::PhongShader() :
    Shader{"res/shaders/phong_vertex.glsl", "res/shaders/phong_fragment.glsl"}
{
    add_uniform("view_position");
}

void PhongShader::set_view_position(const Math::Vector3& position)
{
    set_uniform("view_position", position);
}

void PhongShader::set_uniform(const PointLight& light)
{
    add_uniform("point_light.position");
    set_uniform("point_light.position", light.position);

    add_uniform("point_light.colour");
    set_uniform("point_light.colour", light.colour);

    add_uniform("point_light.constant");
    set_uniform("point_light.constant", light.constant);

    add_uniform("point_light.linear");
    set_uniform("point_light.linear", light.linear);

    add_uniform("point_light.quadratic");
    set_uniform("point_light.quadratic", light.quadratic);
}

void PhongShader::set_uniform(const SpotLight& light)
{
    add_uniform("spot_light.position");
    set_uniform("spot_light.position", light.position);

    add_uniform("spot_light.direction");
    set_uniform("spot_light.direction", light.direction);

    add_uniform("spot_light.colour");
    set_uniform("spot_light.colour", light.colour);

    add_uniform("spot_light.cut_off");
    set_uniform("spot_light.cut_off", light.cut_off);

    add_uniform("spot_light.outer_cut_off");
    set_uniform("spot_light.outer_cut_off", light.outer_cut_off);

    add_uniform("spot_light.constant");
    set_uniform("spot_light.constant", light.constant);

    add_uniform("spot_light.linear");
    set_uniform("spot_light.linear", light.linear);

    add_uniform("spot_light.quadratic");
    set_uniform("spot_light.quadratic", light.quadratic);
}

void PhongShader::set_uniform(const DirectionalLight& light)
{
    add_uniform("directional_light.direction");
    set_uniform("directional_light.direction", light.direction);

    add_uniform("directional_light.colour");
    set_uniform("directional_light.colour", light.colour);
}
