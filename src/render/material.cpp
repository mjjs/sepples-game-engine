#include "material.h"
#include "texture.h"
#include <vector>

Material::Material(
        const std::vector<Texture>& textures,
        const Math::Vector3& ambient_colour,
        const Math::Vector3& diffuse_colour,
        const Math::Vector3& specular_colour
        ) :
    textures_{textures},
    ambient_colour_{ambient_colour},
    diffuse_colour_{diffuse_colour},
    specular_colour_{specular_colour}
{}

std::vector<Texture> Material::textures() const
{
    return textures_;
}

Math::Vector3 Material::ambient_colour() const
{
    return ambient_colour_;
}

Math::Vector3 Material::diffuse_colour() const
{
    return diffuse_colour_;
}

Math::Vector3 Material::specular_colour() const
{
    return specular_colour_;
}

float Material::shininess() const
{
    return shininess_;
}

void Material::set_ambient(const Math::Vector3& colour)
{
    ambient_colour_ = colour;
}

void Material::set_diffuse(const Math::Vector3& colour)
{
    diffuse_colour_ = colour;
}

void Material::set_specular(const Math::Vector3& colour)
{
    specular_colour_ = colour;
}

void Material::set_textures(const std::vector<Texture>& textures)
{
    textures_ = textures;
}

void Material::set_shininess(const float shininess)
{
    shininess_ = shininess;
}
