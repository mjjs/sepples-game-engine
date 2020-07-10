#version 330 core

precision highp float;

in vec4 color;

out vec4 frag_color;

void main()
{
    frag_color = color;
}
