#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 texture_coordinate;

out vec2 texture_coordinate_i;

uniform mat4 transform_u;

void main()
{
    texture_coordinate_i = texture_coordinate;
    gl_Position = transform_u * vec4(position, 1.0);
}
