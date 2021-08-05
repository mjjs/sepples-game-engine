#version 460 core

precision highp float;

struct Material {
    sampler2D texture_diffuse;
    sampler2D texture_specular;
    sampler2D texture_normal;
};

in vec2 texture_coordinate_v;
out vec4 frag_color_v;

uniform Material material_u;

void main()
{
    vec4 diffuse_texture = texture(material_u.texture_diffuse, texture_coordinate_v);
    frag_color_v = diffuse_texture;
}
