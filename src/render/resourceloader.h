#ifndef _GE_RESOURCELOADER_H
#define _GE_RESOURCELOADER_H

#include "mesh.h"
#include "texture.h"
#include <cstdint>
#include <string>

std::string load_shader(const std::string& filename);
std::uint32_t load_texture(const std::string& filename, const std::string& directory);

#endif
