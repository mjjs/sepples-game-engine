#version 460 core

precision highp float;

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

in vec2 out_texture_coordinate_i;
out vec4 frag_color_i;

uniform sampler2D texture_diffuse_u;
uniform Material material_u;

void main()
{
    vec4 texture = texture(texture_diffuse_u, out_texture_coordinate_i);

    vec3 result_colour = material_u.ambient + material_u.diffuse + material_u.specular;

    if (texture == vec4(0.0, 0.0, 0.0, 1.0)) {
        frag_color_i = vec4(result_colour, 1.0);
    } else {
        frag_color_i = texture;
    }
}
