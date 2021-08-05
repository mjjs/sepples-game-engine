#include "resourceloader.h"

#include <fstream>
#include <sstream>
#include <string>

namespace SGE {

std::string load_shader(const std::string& filename)
{
    std::ifstream shader_file{filename, std::ios_base::in};
    std::stringstream ss{};
    ss << shader_file.rdbuf();

    shader_file.close();

    return ss.str();
}

} // namespace SGE
