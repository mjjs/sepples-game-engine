#ifndef _SGE_MATERIAL_H
#define _SGE_MATERIAL_H

#include "vector3.h"

#include <memory>
#include <vector>

namespace SGE
{

class Texture;

class Material
{
  private:
    std::vector<std::shared_ptr<Texture>> textures_{};
    Vector3 ambient_colour_{};
    Vector3 diffuse_colour_{};
    Vector3 specular_colour_{};
    float shininess_ = 1.0F;

  public:
    Material() = default;
    Material(const Vector3& ambient_colour, const Vector3& diffuse_colour,
             const Vector3& specular_colour);

    Material(const std::vector<std::shared_ptr<Texture>>& textures,
             const Vector3& ambient_colour, const Vector3& diffuse_colour,
             const Vector3& specular_colour);

    std::vector<std::shared_ptr<Texture>> textures() const;
    Vector3 ambient_colour() const;
    Vector3 diffuse_colour() const;
    Vector3 specular_colour() const;
    float shininess() const;
    void set_ambient(const Vector3& colour);
    void set_diffuse(const Vector3& colour);
    void set_specular(const Vector3& colour);
    void set_textures(const std::vector<std::shared_ptr<Texture>>& textures);
    void set_shininess(float shininess);
};

} // namespace SGE
#endif
