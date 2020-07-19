#version 330 core

precision highp float;

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

struct DirectionalLight {
    vec3 direction;
    vec3 colour;
};

struct PointLight {
    vec3 position;
    vec3 colour;

    float constant;
    float linear;
    float quadratic;
};

struct SpotLight {
    vec3 position;
    vec3 direction;
    vec3 colour;

    float cut_off;
    float outer_cut_off;

    float constant;
    float linear;
    float quadratic;
};

in vec2 texture_coordinate_i;
in vec3 normal_i;
in vec3 fragment_position_i;

out vec4 frag_color;

uniform sampler2D texture_diffuse1;
uniform sampler2D texture_specular1;

uniform DirectionalLight directional_light;
uniform PointLight point_light;
uniform SpotLight spot_light;

uniform vec3 ambient_light_strength;
uniform vec3 diffuse_light_position;
uniform vec3 view_position;
uniform Material material;

vec3 calculate_directional_light(DirectionalLight light, vec3 normal, vec3 view_direction);
vec3 calculate_point_light(PointLight light, vec3 normal, vec3 fragment_position, vec3 view_direction);
vec3 calculate_spot_light(SpotLight light, vec3 normal, vec3 fragment_position, vec3 view_direction);

void main()
{
    vec3 norm = normalize(normal_i);
    vec3 view_direction = normalize(view_position - fragment_position_i);

    vec3 result = calculate_directional_light(directional_light, norm, view_direction);
    result += calculate_point_light(point_light, norm, fragment_position_i, view_direction);
    result += calculate_spot_light(spot_light, norm, fragment_position_i, view_direction);

    // vec4 material_colour = vec4(ambient_colour + diffuse_colour + specular_colour, 1.0);
    frag_color = vec4(result, 1.0);
}

vec3 calculate_directional_light(DirectionalLight light, vec3 normal, vec3 view_direction)
{
    vec3 light_direction = normalize(-light.direction);
    float diffuse_impact = max(dot(normal, light_direction), 0.0);

    vec3 reflect_direction = reflect(-light_direction, normal);
    float specular_impact = pow(max(dot(view_direction, reflect_direction), 0.0), material.shininess);

    vec3 ambient_colour = light.colour;
    vec3 diffuse_colour = light.colour;

    vec4 diffuse_texture = texture(texture_diffuse1, texture_coordinate_i);
    if (diffuse_texture != vec4(0.0, 0.0, 0.0, 1.0)) {
        ambient_colour *= vec3(diffuse_texture);
        diffuse_colour *= diffuse_impact * vec3(diffuse_texture);
    } else {
        ambient_colour *= material.ambient;
        diffuse_colour *= diffuse_impact * material.diffuse;
    }

    vec3 specular_colour = light.colour;

    vec4 specular_texture = texture(texture_specular1, texture_coordinate_i);
    if (specular_texture != vec4(0.0, 0.0, 0.0, 1.0)) {
        specular_colour *= specular_impact * vec3(specular_texture);
    } else {
        specular_colour *= specular_impact * material.specular;
    }

    return vec3(ambient_colour + diffuse_colour + specular_colour);
}

vec3 calculate_point_light(PointLight light, vec3 normal, vec3 fragment_position, vec3 view_direction)
{
    vec3 light_direction = normalize(light.position - fragment_position);

    float diffuse_impact = max(dot(normal, light_direction), 0.0);

    vec3 reflect_direction = reflect(-light_direction, normal);
    float specular_impact = pow(max(dot(view_direction, reflect_direction), 0.0), material.shininess);

    float distance = length(light.position - fragment_position);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

    vec3 ambient_colour = light.colour;
    vec3 diffuse_colour = light.colour;

    vec4 diffuse_texture = texture(texture_diffuse1, texture_coordinate_i);
    if (diffuse_texture != vec4(0.0, 0.0, 0.0, 1.0)) {
        ambient_colour *= vec3(diffuse_texture);
        diffuse_colour *= diffuse_impact * vec3(diffuse_texture);
    } else {
        ambient_colour *= material.ambient;
        diffuse_colour *= diffuse_impact * material.diffuse;
    }

    vec3 specular_colour = light.colour;

    vec4 specular_texture = texture(texture_specular1, texture_coordinate_i);
    if (specular_texture != vec4(0.0, 0.0, 0.0, 1.0)) {
        specular_colour *= specular_impact * vec3(specular_texture);
    } else {
        specular_colour *= specular_impact * material.specular;
    }

    ambient_colour *= attenuation;
    diffuse_colour *= attenuation;
    specular_colour *= attenuation;

    return vec3(ambient_colour + diffuse_colour + specular_colour);
}

vec3 calculate_spot_light(SpotLight light, vec3 normal, vec3 fragment_position, vec3 view_direction)
{
    vec3 light_direction = normalize(light.position - fragment_position);

    float diffuse_impact = max(dot(normal, light_direction), 0.0);
    vec3 reflect_direction = reflect(-light_direction, normal);
    float specular_impact = pow(max(dot(view_direction, reflect_direction), 0.0), material.shininess);

    float distance = length(light.position - fragment_position);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

    float theta = dot(light_direction, normalize(-light.direction));
    float epsilon = light.cut_off - light.outer_cut_off;
    float intensity = clamp((theta - light.outer_cut_off) / epsilon, 0.0, 1.0);

    vec3 ambient_colour = light.colour;
    vec3 diffuse_colour = light.colour;

    vec4 diffuse_texture = texture(texture_diffuse1, texture_coordinate_i);
    if (diffuse_texture != vec4(0.0, 0.0, 0.0, 1.0)) {
        ambient_colour *= vec3(diffuse_texture);
        diffuse_colour *= diffuse_impact * vec3(diffuse_texture);
    } else {
        ambient_colour *= material.ambient;
        diffuse_colour *= diffuse_impact * material.diffuse;
    }

    vec3 specular_colour = light.colour;

    vec4 specular_texture = texture(texture_specular1, texture_coordinate_i);
    if (specular_texture != vec4(0.0, 0.0, 0.0, 1.0)) {
        specular_colour *= specular_impact * vec3(specular_texture);
    } else {
        specular_colour *= specular_impact * material.specular;
    }

    ambient_colour *= attenuation * intensity;
    diffuse_colour *= attenuation * intensity;
    specular_colour *= attenuation * intensity;

    return vec3(ambient_colour + diffuse_colour + specular_colour);
}
