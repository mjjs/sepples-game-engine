#include "material.h"
#include "texture.h"
#include <vector>

namespace SGE {

Material::Material(
        const std::vector<Texture>& textures,
        const Vector3& ambient_colour,
        const Vector3& diffuse_colour,
        const Vector3& specular_colour
        ) :
    textures_{textures},
    ambient_colour_{ambient_colour},
    diffuse_colour_{diffuse_colour},
    specular_colour_{specular_colour}
{}

Material::Material(
        const Vector3& ambient_colour,
        const Vector3& diffuse_colour,
        const Vector3& specular_colour
        ) :
    ambient_colour_{ambient_colour},
    diffuse_colour_{diffuse_colour},
    specular_colour_{specular_colour}
{}

} // namespace SGE
