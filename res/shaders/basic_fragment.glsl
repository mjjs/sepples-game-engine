#version 330 core

precision highp float;

in vec2 texture_coordinate_i;
out vec4 frag_color_i;

uniform sampler2D texture_diffuse1_u;
uniform vec3 ambient_colour_u;
uniform vec3 diffuse_colour_u;
uniform vec3 specular_colour_u;

void main()
{
    vec4 texture = texture(texture_diffuse1_u, texture_coordinate_i);

    vec3 result_colour = ambient_colour_u + diffuse_colour_u + specular_colour_u;

    if (texture == vec4(0.0, 0.0, 0.0, 1.0)) {
        frag_color_i = vec4(result_colour, 1.0);
    } else {
        frag_color_i = texture;
    }
}
