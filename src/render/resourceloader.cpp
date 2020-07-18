#include "mesh.h"
#include "resourceloader.h"
#include "sgestrings.h"
#include "texture.h"
#include "vector2.h"
#include "vector3.h"
#include "vertex.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <GL/glew.h>

#include <cstdint>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

std::string load_shader(const std::string& filename)
{
    std::ifstream shader_file{filename, std::ios_base::in};
    std::stringstream ss{};
    ss << shader_file.rdbuf();

    shader_file.close();

    return ss.str();
}

std::uint32_t load_texture(const std::string& filename, const std::string& directory)
{
    std::string file_location = directory + '/' + filename;

    GLuint texture_id;
    glGenTextures(1, &texture_id);

    int width;
    int height;
    int channel_amount;

    unsigned char* image_bytes = stbi_load(file_location.c_str(), &width, &height, &channel_amount, 0);

    if (image_bytes == nullptr) {
        stbi_image_free(image_bytes);
        throw std::runtime_error("Could not load texture " + file_location);
    }

    GLenum format;
    if (channel_amount == 1) {
        format = GL_RED;
    } else if (channel_amount == 3) {
        format = GL_RGB;
    } else if (channel_amount == 4) {
        format = GL_RGBA;
    } else {
        throw std::runtime_error("Mystery channel amount in load_shader function");
    }

    glBindTexture(GL_TEXTURE_2D, texture_id);
    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, image_bytes);
    glGenerateMipmap(GL_TEXTURE_2D);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    stbi_image_free(image_bytes);

    return texture_id;
}
