#version 460 core

layout(location = 0) in vec3 position_l;
layout(location = 1) in vec4 colour_l;
layout(location = 2) in vec2 texture_coordinate_l;
layout(location = 3) in float texture_index_l;

out vec4 colour_v;
out vec2 texture_coordinate_v;
out float texture_index_v;

layout(std140, binding = 1) uniform Camera {
    mat4 view_projection_u;
};

void main()
{
    gl_Position = view_projection_u * vec4(position_l, 1.0);

    colour_v = colour_l;
    texture_coordinate_v = texture_coordinate_l;
    texture_index_v = texture_index_l;
}
