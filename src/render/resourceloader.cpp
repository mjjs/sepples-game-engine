#include "resourceloader.h"
#include <fstream>
#include <sstream>
#include <string>

std::string load_shader(const std::string& filename)
{
    std::ifstream shader_file{"./res/shaders/" + filename, std::ios_base::in};
    std::stringstream ss{};
    ss << shader_file.rdbuf();

    return ss.str();
}
