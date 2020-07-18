#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 texture_coordinate;

out vec2 texture_coordinate_i;
out vec3 normal_i;
out vec3 fragment_position_i;

uniform mat4 projection;
uniform mat4 transform;

void main()
{
    texture_coordinate_i = texture_coordinate;
    normal_i = normal;
    gl_Position = projection * vec4(position, 1.0);
    fragment_position_i = vec3(transform * vec4(position, 1.0));
}
