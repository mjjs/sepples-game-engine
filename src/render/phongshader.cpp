#include "directionallight.h"
#include "phongshader.h"
#include "pointlight.h"
#include "spotlight.h"
#include "shader.h"
#include "vector3.h"

PhongShader::PhongShader() :
    Shader{"res/shaders/phong_vertex.glsl", "res/shaders/phong_fragment.glsl"}
{
    add_uniform("view_position_u");
}

void PhongShader::set_view_position(const Math::Vector3& position)
{
    set_uniform("view_position_u", position);
}

void PhongShader::set_uniform(const PointLight& light)
{
    add_uniform("point_light_u.position");
    set_uniform("point_light_u.position", light.position);

    add_uniform("point_light_u.colour");
    set_uniform("point_light_u.colour", light.colour);

    add_uniform("point_light_u.constant");
    set_uniform("point_light_u.constant", light.constant);

    add_uniform("point_light_u.linear");
    set_uniform("point_light_u.linear", light.linear);

    add_uniform("point_light_u.quadratic");
    set_uniform("point_light_u.quadratic", light.quadratic);
}

void PhongShader::set_uniform(const SpotLight& light)
{
    add_uniform("spot_light_u.position");
    set_uniform("spot_light_u.position", light.position);

    add_uniform("spot_light_u.direction");
    set_uniform("spot_light_u.direction", light.direction);

    add_uniform("spot_light_u.colour");
    set_uniform("spot_light_u.colour", light.colour);

    add_uniform("spot_light_u.cut_off");
    set_uniform("spot_light_u.cut_off", light.cut_off);

    add_uniform("spot_light_u.outer_cut_off");
    set_uniform("spot_light_u.outer_cut_off", light.outer_cut_off);

    add_uniform("spot_light_u.constant");
    set_uniform("spot_light_u.constant", light.constant);

    add_uniform("spot_light_u.linear");
    set_uniform("spot_light_u.linear", light.linear);

    add_uniform("spot_light_u.quadratic");
    set_uniform("spot_light_u.quadratic", light.quadratic);
}

void PhongShader::set_uniform(const DirectionalLight& light)
{
    add_uniform("directional_light_u.direction");
    set_uniform("directional_light_u.direction", light.direction);

    add_uniform("directional_light_u.colour");
    set_uniform("directional_light_u.colour", light.colour);
}
