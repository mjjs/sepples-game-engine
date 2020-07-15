#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 texture_coordinate;

out vec2 out_texture_coordinate;

uniform mat4 transform;

void main()
{
    out_texture_coordinate = texture_coordinate;
    gl_Position = transform * vec4(position, 1.0);
}
