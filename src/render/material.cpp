#include "material.h"
#include "texture.h"
#include <vector>

namespace SGE {

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

Material::Material(
        const Math::Vector3& ambient_colour,
        const Math::Vector3& diffuse_colour,
        const Math::Vector3& specular_colour
        ) :
    ambient_colour_{ambient_colour},
    diffuse_colour_{diffuse_colour},
    specular_colour_{specular_colour}
{}

} // namespace SGE
