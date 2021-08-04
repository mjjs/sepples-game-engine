#ifndef _SGE_TEXTURE_H
#define _SGE_TEXTURE_H

#include <assimp/material.h>
#include <cstdint>
#include <string>

namespace SGE
{

enum TextureType {
    DIFFUSE,
    SPECULAR,
    NORMAL,
};

struct Texture {
    std::uint32_t id;
    TextureType type;
    std::string filename;
};

Texture load_texture(const std::string& filename, const std::string& directory,
                     TextureType texture_type);
Texture load_diffuse_texture(const std::string& filename,
                             const std::string& directory);
Texture load_specular_texture(const std::string& filename,
                              const std::string& directory);
Texture load_normal_texture(const std::string& filename,
                            const std::string& directory);

aiTextureType from_texture_type(TextureType texture_type);

} // namespace SGE

#endif
