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

        inline std::vector<Texture> textures() const
        {
            return textures_;
        }

        inline Math::Vector3 ambient_colour() const
        {
            return ambient_colour_;
        }

        inline Math::Vector3 diffuse_colour() const
        {
            return diffuse_colour_;
        }

        inline Math::Vector3 specular_colour() const
        {
            return specular_colour_;
        }

        inline float shininess() const
        {
            return shininess_;
        }

        inline void set_ambient(const Math::Vector3& colour)
        {
            ambient_colour_ = colour;
        }

        inline void set_diffuse(const Math::Vector3& colour)
        {
            diffuse_colour_ = colour;
        }

        inline void set_specular(const Math::Vector3& colour)
        {
            specular_colour_ = colour;
        }

        inline void set_textures(const std::vector<Texture>& textures)
        {
            textures_ = textures;
        }

        inline void set_shininess(float shininess)
        {
            shininess_ = shininess;
        }
};

} // namespace SGE
#endif
