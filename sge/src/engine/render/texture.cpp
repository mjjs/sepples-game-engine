#define STB_IMAGE_IMPLEMENTATION

#include "stb_image.h"
#include "texture.h"

#include <assimp/material.h>
#include <cstdint>
#include <stdexcept>
#include <glad/glad.h>

namespace SGE {

Texture load_texture(const std::string& filename, const std::string& directory, TextureType texture_type)
{
    std::string file_location = directory + '/' + filename;

    GLuint texture_id = -1;
    glGenTextures(1, &texture_id);

    int width{};
    int height{};
    int channel_amount{};

    unsigned char* image_bytes = stbi_load(file_location.c_str(), &width, &height, &channel_amount, 0);

    if (image_bytes == nullptr) {
        stbi_image_free(image_bytes);
        throw std::runtime_error("Could not load texture " + file_location);
    }

    GLenum format{};
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
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    stbi_image_free(image_bytes);

    return Texture{texture_id, texture_type, filename};
}

Texture load_diffuse_texture(const std::string& filename, const std::string& directory)
{
    return load_texture(filename, directory, TextureType::DIFFUSE);
}

Texture load_specular_texture(const std::string& filename, const std::string& directory)
{
    return load_texture(filename, directory, TextureType::SPECULAR);
}

Texture load_normal_texture(const std::string& filename, const std::string& directory)
{
    return load_texture(filename, directory, TextureType::NORMAL);
}

aiTextureType from_texture_type(const TextureType texture_type)
{
    switch (texture_type) {
    case TextureType::DIFFUSE:
        return aiTextureType_DIFFUSE;
    case TextureType::NORMAL:
        return aiTextureType_NORMALS;
    case TextureType::SPECULAR:
        return aiTextureType_SPECULAR;
    default:
        throw std::runtime_error{"Texture type not supported"};
    }
}

} // namespace SGE
