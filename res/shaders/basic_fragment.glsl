#version 330 core

precision highp float;

in vec2 out_texture_coordinate;
out vec4 frag_color;

uniform sampler2D texture_diffuse1;

void main()
{
    frag_color = texture(texture_diffuse1, out_texture_coordinate);
}
