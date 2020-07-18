#version 330 core

precision highp float;

in vec2 out_texture_coordinate;
out vec4 frag_color;

uniform sampler2D texture_diffuse1;
uniform vec3 ambient_colour;
uniform vec3 diffuse_colour;
uniform vec3 specular_colour;

void main()
{
    vec4 texture = texture(texture_diffuse1, out_texture_coordinate);

    vec3 result_colour = ambient_colour + diffuse_colour + specular_colour;

    if (texture == vec4(0.0, 0.0, 0.0, 1.0)) {
        frag_color = vec4(result_colour, 1.0);
    } else {
        frag_color = texture;
    }
}
