#version 460 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 texture_coordinate;

out vec2 texture_coordinate0;
out vec3 normal0;
out vec3 fragment_position0;

layout(row_major, std140, binding = 0) uniform Camera {
    mat4 view_projection_u;
};
uniform mat4 transform_u;

void main()
{
    gl_Position = view_projection_u * transform_u * vec4(position, 1.0);
    texture_coordinate0 = texture_coordinate;
    normal0 = (transform_u * vec4(normal, 0.0)).xyz;
    fragment_position0 = (transform_u * vec4(position, 1.0)).xyz;
}
