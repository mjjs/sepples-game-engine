#include "mesh.h"
#include "resourceloader.h"
#include "sgestrings.h"
#include "vector3.h"

#include <fstream>
#include <sstream>
#include <stdexcept>
#include <string>

std::string load_shader(const std::string& filename)
{
    std::ifstream shader_file{"./res/shaders/" + filename, std::ios_base::in};
    std::stringstream ss{};
    ss << shader_file.rdbuf();

    return ss.str();
}

Mesh load_mesh(const std::string& filename)
{
    const std::vector<std::string> filename_parts = split(filename, '.');
    if (filename_parts.empty()) {
        throw std::runtime_error("Mesh object file " + filename + " has no extension");
    }

    const std::string extension = filename_parts[filename_parts.size() - 1];

    if (extension != "obj") {
        throw std::runtime_error("Unsupported mesh file extension: " + extension);
    }

    std::vector<Math::Vector3> vertices{};
    std::vector<int> indices{};

    std::ifstream mesh_file{"./res/models/" + filename, std::ios_base::in};
    std::string line{};

    while (std::getline(mesh_file, line)) {
        const std::vector<std::string> tokens = split(line, ' ');

        if (tokens.empty() || tokens[0] == "#") {
            continue;
        }

        if (tokens[0] == "v") {
            vertices.emplace_back(Math::Vector3{
                    std::stof(tokens[1], nullptr),
                    std::stof(tokens[2], nullptr),
                    std::stof(tokens[3], nullptr)
                    });
            continue;
        }

        if (tokens[0] == "f") {
            indices.push_back(std::stoi(tokens[1], nullptr, 10) - 1);
            indices.push_back(std::stoi(tokens[2], nullptr, 10) - 1);
            indices.push_back(std::stoi(tokens[3], nullptr, 10) - 1);
            continue;
        }
    }

    return Mesh{vertices, indices};
}
