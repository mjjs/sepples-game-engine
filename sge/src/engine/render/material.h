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

        std::vector<Texture> textures() const;
        Vector3 ambient_colour() const;
        Vector3 diffuse_colour() const;
        Vector3 specular_colour() const;
        float shininess() const;
        void set_ambient(const Vector3& colour);
        void set_diffuse(const Vector3& colour);
        void set_specular(const Vector3& colour);
        void set_textures(const std::vector<Texture>& textures);
        void set_shininess(float shininess);
};

} // namespace SGE
#endif
