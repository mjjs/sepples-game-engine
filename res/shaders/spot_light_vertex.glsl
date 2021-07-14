#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 texture_coordinate;

out vec2 texture_coordinate0;
out vec3 normal0;
out vec3 fragment_position0;

uniform mat4 transform_u;
uniform mat4 projection_u;

void main()
{
    gl_Position = transform_u * vec4(position, 1.0);
    texture_coordinate0 = texture_coordinate;
    normal0 = (projection_u * vec4(normal, 0.0)).xyz;
    fragment_position0 = (projection_u * vec4(position, 1.0)).xyz;
}
