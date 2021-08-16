#ifndef _SGE_MATERIAL_H
#define _SGE_MATERIAL_H


#include <memory>
#include <vector>

namespace SGE
{

class Texture;

class Material
{
  private:
    std::shared_ptr<Texture> diffuse_texture_;
    std::shared_ptr<Texture> specular_texture_;
    std::shared_ptr<Texture> normal_texture_;

    float shininess_ = 1.0F;

  public:
    Material();
    Material(const std::shared_ptr<Texture>& diffuse_texture,
             const std::shared_ptr<Texture>& specular_texture,
             const std::shared_ptr<Texture>& normal_texture,
             float shininess = 1.0F);

    const std::shared_ptr<Texture>& diffuse_texture() const;
    const std::shared_ptr<Texture>& specular_texture() const;
    const std::shared_ptr<Texture>& normal_texture() const;
    float shininess() const;
};

} // namespace SGE
#endif
