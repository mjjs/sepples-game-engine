#ifndef _SGE_TEXTURE_H
#define _SGE_TEXTURE_H
#include <cstdint>
#include <string>

struct Texture {
    std::uint32_t id;
    std::string type;
    std::string path;
};

#endif
