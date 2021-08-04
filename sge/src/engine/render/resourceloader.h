#ifndef _SGE_RESOURCELOADER_H
#define _SGE_RESOURCELOADER_H

#include "mesh.h"
#include "texture.h"

#include <cstdint>
#include <string>

namespace SGE {

std::string load_shader(const std::string& filename);

} // namespace SGE

#endif
