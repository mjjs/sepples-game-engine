#ifndef _SGE_MATERIAL_H
#define _SGE_MATERIAL_H

#include "texture.h"
#include "vector3.h"
#include <vector>

namespace SGE {

class Material {
    private:
        std::vector<Texture> textures_{};
        Vector3 ambient_colour_{};
        Vector3 diffuse_colour_{};
        Vector3 specular_colour_{};
        float shininess_ = 1.0F;

    public:
        Material() = default;
        Material(
                const Vector3& ambient_colour,
                const Vector3& diffuse_colour,
                const Vector3& specular_colour
                );

        explicit Material(
                const std::vector<Texture>& textures,
                const Vector3& ambient_colour,
                const Vector3& diffuse_colour,
                const Vector3& specular_colour
                );

        inline std::vector<Texture> textures() const
        {
            return textures_;
        }

        inline Vector3 ambient_colour() const
        {
            return ambient_colour_;
        }

        inline Vector3 diffuse_colour() const
        {
            return diffuse_colour_;
        }

        inline Vector3 specular_colour() const
        {
            return specular_colour_;
        }

        inline float shininess() const
        {
            return shininess_;
        }

        inline void set_ambient(const Vector3& colour)
        {
            ambient_colour_ = colour;
        }

        inline void set_diffuse(const Vector3& colour)
        {
            diffuse_colour_ = colour;
        }

        inline void set_specular(const Vector3& colour)
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
