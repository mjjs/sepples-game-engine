#include "engine/rendering/material.h"

#include "engine/rendering/texture.h"
#include "engine/rendering/texture2d.h"
#include "engine/math/vector3.h"

#include <memory>
#include <vector>

namespace SGE
{

Material::Material()
    : diffuse_texture_{Texture2D::create(Vector3{1, 0, 1}, 1, 1)}
{
}

Material::Material(const std::shared_ptr<Texture>& diffuse_texture,
                   const std::shared_ptr<Texture>& specular_texture,
                   const std::shared_ptr<Texture>& normal_texture,
                   float shininess)
    : diffuse_texture_{diffuse_texture}, specular_texture_{specular_texture},
      normal_texture_{normal_texture}, shininess_{shininess}
{
    if (diffuse_texture == nullptr) {
        diffuse_texture_ = Texture2D::create(Vector3{1, 0, 1}, 1, 1);
    }
}

const std::shared_ptr<Texture>& Material::diffuse_texture() const
{
    return diffuse_texture_;
}

const std::shared_ptr<Texture>& Material::specular_texture() const
{
    return specular_texture_;
}

const std::shared_ptr<Texture>& Material::normal_texture() const
{
    return normal_texture_;
}

float Material::shininess() const
{
    return shininess_;
}

} // namespace SGE
