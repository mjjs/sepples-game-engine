#ifndef _SGE_MATERIAL_H
#define _SGE_MATERIAL_H

#include "texture.h"
#include "vector3.h"
#include <vector>

namespace SGE {

class Material {
    private:
        std::vector<Texture> textures_{};
        Math::Vector3 ambient_colour_{};
        Math::Vector3 diffuse_colour_{};
        Math::Vector3 specular_colour_{};
        float shininess_ = 1.0F;

    public:
        Material() = default;
        Material(
                const Math::Vector3& ambient_colour,
                const Math::Vector3& diffuse_colour,
                const Math::Vector3& specular_colour
                );

        explicit Material(
                const std::vector<Texture>& textures,
                const Math::Vector3& ambient_colour,
                const Math::Vector3& diffuse_colour,
                const Math::Vector3& specular_colour
                );

        std::vector<Texture> textures() const;
        Math::Vector3 ambient_colour() const;
        Math::Vector3 diffuse_colour() const;
        Math::Vector3 specular_colour() const;
        float shininess() const;

        void set_ambient(const Math::Vector3& colour);
        void set_diffuse(const Math::Vector3& colour);
        void set_specular(const Math::Vector3& colour);
        void set_textures(const std::vector<Texture>& textures);
        void set_shininess(float shininess);
};

} // namespace SGE
#endif
