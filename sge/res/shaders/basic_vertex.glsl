#version 460 core

layout(location = 0) in vec3 position_i;
layout(location = 1) in vec3 normal_i;
layout(location = 2) in vec2 texture_coordinate_i;

out vec2 out_texture_coordinate_i;

layout(row_major, std140, binding = 0) uniform Camera {
    mat4 view_projection_u;
};
uniform mat4 transform_u;

void main()
{
    gl_Position = view_projection_u * transform_u * vec4(position_i, 1.0);
    out_texture_coordinate_i = texture_coordinate_i;
}
