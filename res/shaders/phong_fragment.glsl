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

out vec4 frag_color_i;

uniform sampler2D texture_diffuse1_u;
uniform sampler2D texture_specular1_u;
uniform Material material_u;

uniform DirectionalLight directional_light_u;
uniform PointLight point_light_u;
uniform SpotLight spot_light_u;
uniform vec3 view_position_u;

vec3 calculate_directional_light(DirectionalLight light, vec3 normal, vec3 view_direction);
vec3 calculate_point_light(PointLight light, vec3 normal, vec3 fragment_position, vec3 view_direction);
vec3 calculate_spot_light(SpotLight light, vec3 normal, vec3 fragment_position, vec3 view_direction);
vec3 get_texture_or_material_colour(vec4 texture, vec3 material);

float calculate_diffuse_impact(vec3 normal, vec3 light_direction);
float calculate_specular_impact(vec3 view_direction, vec3 reflect_direction);

void main()
{
    vec3 norm = normalize(normal_i);
    vec3 view_direction = normalize(view_position_u - fragment_position_i);

    vec3 result = calculate_directional_light(directional_light_u, norm, view_direction);
    result += calculate_point_light(point_light_u, norm, fragment_position_i, view_direction);
    result += calculate_spot_light(spot_light_u, norm, fragment_position_i, view_direction);

    frag_color_i = vec4(result, 1.0);
}

vec3 calculate_directional_light(DirectionalLight light, vec3 normal, vec3 view_direction)
{
    vec3 light_direction = normalize(-light.direction);
    float diffuse_impact = calculate_diffuse_impact(normal, light_direction);

    vec3 reflect_direction = reflect(-light_direction, normal);
    float specular_impact = calculate_specular_impact(view_direction, reflect_direction);

    vec4 diffuse_texture = texture(texture_diffuse1_u, texture_coordinate_i);
    vec4 specular_texture = texture(texture_specular1_u, texture_coordinate_i);

    vec3 ambient_colour = light.colour * get_texture_or_material_colour(diffuse_texture, material_u.ambient);
    vec3 diffuse_colour = light.colour * diffuse_impact * get_texture_or_material_colour(diffuse_texture, material_u.diffuse);
    vec3 specular_colour = light.colour * specular_impact * get_texture_or_material_colour(specular_texture, material_u.specular);

    return vec3(ambient_colour + diffuse_colour + specular_colour);
}

vec3 calculate_point_light(PointLight light, vec3 normal, vec3 fragment_position, vec3 view_direction)
{
    vec3 light_direction = normalize(light.position - fragment_position);

    float diffuse_impact = calculate_diffuse_impact(normal, light_direction);

    vec3 reflect_direction = reflect(-light_direction, normal);
    float specular_impact = calculate_specular_impact(view_direction, reflect_direction);

    float distance = length(light.position - fragment_position);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

    vec4 diffuse_texture = texture(texture_diffuse1_u, texture_coordinate_i);
    vec4 specular_texture = texture(texture_specular1_u, texture_coordinate_i);

    vec3 ambient_colour = light.colour * get_texture_or_material_colour(diffuse_texture, material_u.ambient);
    vec3 diffuse_colour = light.colour * diffuse_impact * get_texture_or_material_colour(diffuse_texture, material_u.diffuse);
    vec3 specular_colour = light.colour * specular_impact * get_texture_or_material_colour(specular_texture, material_u.specular);

    ambient_colour *= attenuation;
    diffuse_colour *= attenuation;
    specular_colour *= attenuation;

    return vec3(ambient_colour + diffuse_colour + specular_colour);
}

vec3 calculate_spot_light(SpotLight light, vec3 normal, vec3 fragment_position, vec3 view_direction)
{
    vec3 light_direction = normalize(light.position - fragment_position);

    float diffuse_impact = calculate_diffuse_impact(normal, light_direction);
    vec3 reflect_direction = reflect(-light_direction, normal);
    float specular_impact = calculate_specular_impact(view_direction, reflect_direction);

    float distance = length(light.position - fragment_position);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

    float theta = dot(light_direction, normalize(-light.direction));
    float epsilon = light.cut_off - light.outer_cut_off;
    float intensity = clamp((theta - light.outer_cut_off) / epsilon, 0.0, 1.0);

    vec4 diffuse_texture = texture(texture_diffuse1_u, texture_coordinate_i);
    vec4 specular_texture = texture(texture_specular1_u, texture_coordinate_i);

    vec3 ambient_colour = light.colour * get_texture_or_material_colour(diffuse_texture, material_u.ambient);
    vec3 diffuse_colour = light.colour * diffuse_impact * get_texture_or_material_colour(diffuse_texture, material_u.diffuse);
    vec3 specular_colour = light.colour * specular_impact * get_texture_or_material_colour(specular_texture, material_u.specular);

    ambient_colour *= attenuation * intensity;
    diffuse_colour *= attenuation * intensity;
    specular_colour *= attenuation * intensity;

    return vec3(ambient_colour + diffuse_colour + specular_colour);
}

vec3 get_texture_or_material_colour(vec4 texture, vec3 material)
{
    if (texture == vec4(0.0, 0.0, 0.0, 1.0)) {
        return material;
    }

    return texture.xyz;
}

float calculate_diffuse_impact(vec3 normal, vec3 light_direction)
{
    return max(dot(normal, light_direction), 0.0);
}

float calculate_specular_impact(vec3 view_direction, vec3 reflect_direction)
{
    return pow(max(dot(view_direction, reflect_direction), 0.0), material_u.shininess);
}
