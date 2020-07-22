#ifndef _SGE_TEXTURE_H
#define _SGE_TEXTURE_H

#include <assimp/material.h>
#include <cstdint>
#include <string>

struct Texture {
    std::uint32_t id;
    aiTextureType type;
    std::string path;
};

#endif
