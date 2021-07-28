#version 460 core

precision highp float;

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

struct Light {
    vec3 colour;
    float intensity;
};

struct Attenuation {
    float constant;
    float linear;
    float quadratic;
};

struct PointLight {
    Light base;
    Attenuation attenuation;
    vec3 position;
};

in vec2 texture_coordinate0;
in vec3 normal0;
in vec3 fragment_position0;

out vec4 frag_color;

uniform sampler2D texture_diffuse1_u;
uniform sampler2D texture_specular1_u;
uniform Material material_u;
uniform PointLight point_light_u;
uniform vec3 view_position_u;

vec3 calculate_light(Light light, vec3 direction, vec3 normal, vec3 view_direction);
vec3 calculate_point_light(PointLight light, vec3 normal, vec3 fragment_position, vec3 view_direction);

vec3 get_texture_or_material_colour(vec4 texture, vec3 material);

float calculate_diffuse_impact(vec3 normal, vec3 light_direction);
float calculate_specular_impact(vec3 view_direction, vec3 reflect_direction);

void main()
{
    vec3 norm = normalize(normal0);
    vec3 view_direction = normalize(view_position_u - fragment_position0);

    vec3 result = calculate_point_light(point_light_u, norm, fragment_position0, view_direction);

    frag_color = vec4(result, 1.0);
}

vec3 get_texture_or_material_colour(vec4 texture, vec3 material)
{
    if (texture == vec4(0.0, 0.0, 0.0, 1.0)) {
        return material;
    }

    return texture.xyz;
}

vec3 calculate_light(Light light, vec3 direction, vec3 normal, vec3 view_direction)
{
    vec3 reflect_direction = normalize(reflect(-direction, normal));

    float diffuse_impact = calculate_diffuse_impact(normal, direction);
    float specular_impact = calculate_specular_impact(view_direction, reflect_direction);

    vec4 diffuse_texture = texture(texture_diffuse1_u, texture_coordinate0);
    vec4 specular_texture = texture(texture_specular1_u, texture_coordinate0);

    vec3 diffuse_colour = light.colour * diffuse_impact * get_texture_or_material_colour(diffuse_texture, material_u.diffuse);
    vec3 specular_colour = light.colour * specular_impact * get_texture_or_material_colour(specular_texture, material_u.specular);

    return (diffuse_colour + specular_colour) * light.intensity;
}

vec3 calculate_point_light(PointLight light, vec3 normal, vec3 fragment_position, vec3 view_direction)
{
    vec3 light_direction = normalize(light.position - fragment_position);
    vec3 colour = calculate_light(light.base, light_direction, normal, view_direction);

    float dist = length(light.position - fragment_position);
    float attenuation = 1.0 / (light.attenuation.constant + light.attenuation.linear *
                               dist + light.attenuation.quadratic * (dist * dist));

    return colour * attenuation;
}

float calculate_diffuse_impact(vec3 normal, vec3 light_direction)
{
    return max(dot(normal, light_direction), 0.0);
}

float calculate_specular_impact(vec3 view_direction, vec3 reflect_direction)
{
    return pow(max(dot(view_direction, reflect_direction), 0.0), material_u.shininess);
}
