#version 330 core

precision highp float;

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

in vec2 texture_coordinate_i;
in vec3 normal_i;
in vec3 fragment_position_i;

out vec4 frag_color;

uniform sampler2D texture_diffuse1;
uniform vec3 ambient_light_strength;
uniform vec3 diffuse_light_position;
uniform vec3 view_position;
uniform Material material;

vec3 calculate_diffuse_colour(vec3 normal, vec3 light_direction, vec3 material_colour)
{
    float diff = max(dot(normal, light_direction), 0.0);
    return diff * material_colour;
}

vec3 calculate_specular_colour(vec3 view_direction, vec3 reflect_direction, vec3 material_colour)
{
    float specular_strength = 0.5;
    float spec = pow(max(dot(view_direction, reflect_direction), 0.0), material.shininess);

    return specular_strength * spec * material_colour;
}

void main()
{
    vec3 ambient_colour = ambient_light_strength * material.ambient;

    vec3 norm = normalize(normal_i);
    vec3 light_direction = normalize(diffuse_light_position - fragment_position_i);

    vec3 diffuse_colour = calculate_diffuse_colour(norm, light_direction, material.diffuse);

    vec3 view_direction = normalize(view_position - fragment_position_i);
    vec3 reflect_direction = reflect(-light_direction, norm);
    vec3 specular_colour = calculate_specular_colour(view_direction, reflect_direction, material.specular);

    vec4 material_colour = vec4(ambient_colour + diffuse_colour + specular_colour, 1.0);

    frag_color = material_colour;

    vec4 texture = texture(texture_diffuse1, texture_coordinate_i);
    if (texture != vec4(0.0, 0.0, 0.0, 1.0)) {
        frag_color *= texture;
    }
}
