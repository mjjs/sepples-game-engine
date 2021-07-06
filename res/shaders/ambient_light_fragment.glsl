#version 330 core

precision highp float;

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

in vec2 texture_coordinate_0;
out vec4 fragment_colour;

uniform sampler2D texture_diffuse1_u;
uniform Material material_u;
uniform vec3 intensity_u;

void main()
{
    vec4 texture = texture(texture_diffuse1_u, texture_coordinate_0);

    if (texture == vec4(0.0, 0.0, 0.0, 1.0)) {
        fragment_colour = vec4(material_u.ambient * intensity_u, 1.0);
    } else {
        fragment_colour = vec4(texture.xyz * intensity_u, 1.0);
    }
}
