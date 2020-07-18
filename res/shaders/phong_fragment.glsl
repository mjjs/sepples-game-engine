#version 330 core

precision highp float;

in vec2 out_texture_coordinate;
out vec4 frag_color;

uniform sampler2D texture_diffuse1;

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform vec3 ambient_light_strength;
uniform Material material;

void main()
{
    vec3 ambient_colour = ambient_light_strength * material.ambient;

    vec4 material_colour = vec4(
        ambient_colour + material.diffuse + material.specular,
        1.0
        );

    frag_color = material_colour;

    vec4 texture = texture(texture_diffuse1, out_texture_coordinate);
    if (texture != vec4(0.0, 0.0, 0.0, 1.0)) {
        frag_color *= texture;
    }
}
