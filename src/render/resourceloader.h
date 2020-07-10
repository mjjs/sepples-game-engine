#ifndef _GE_RESOURCELOADER_H
#define _GE_RESOURCELOADER_H

#include "mesh.h"
#include <string>

std::string load_shader(const std::string& filename);
Mesh load_mesh(const std::string& filename);

#endif
