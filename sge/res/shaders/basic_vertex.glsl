#version 460 core

layout(location = 0) in vec3 position_l;
layout(location = 1) in vec3 normal_l;
layout(location = 2) in vec2 texture_coordinate_l;

out vec2 texture_coordinate_v;

layout(std140, binding = 0) uniform Camera {
    mat4 view_projection_u;
};

uniform mat4 transform_u;

void main()
{
    gl_Position = view_projection_u * transform_u * vec4(position_l, 1.0);
    texture_coordinate_v = texture_coordinate_l;
}
