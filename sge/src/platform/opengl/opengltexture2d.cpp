#include "opengltexture2d.h"

#include "log.h"
#include "stb_image.h"

#include <cmath>
#include <cstdint>
#include <glad/glad.h>
#include <stdexcept>
#include <string>

namespace SGE
{

static std::uint32_t colour_vector_to_hex(const Vector3& rgb)
{
    const std::uint32_t r = std::floor(rgb.x >= 1.0 ? 255 : rgb.x * 256.0);
    const std::uint32_t g = std::floor(rgb.y >= 1.0 ? 255 : rgb.y * 256.0);
    const std::uint32_t b = std::floor(rgb.z >= 1.0 ? 255 : rgb.z * 256.0);

    std::uint32_t hex = ((b & 0xFF) << 16) + ((g & 0xFF) << 8) + (r & 0xFF);

    return hex;
}

OpenGLTexture2D::OpenGLTexture2D(const std::string& path,
                                 const Texture::Type type)
    : texture_id_{0}, path_{path}, type_{type}
{
    int width{};
    int height{};
    int channel_amount{};

    LOG_INFO("Loading texture {0}", path);
    auto* texture_bytes =
        stbi_load(path.c_str(), &width, &height, &channel_amount, 0);

    GLenum format{};
    GLenum sub_format{};

    switch (channel_amount) {
    case 1:
        format     = GL_RED;
        sub_format = GL_RED;
        break;
    case 3:
        format     = GL_RGB8;
        sub_format = GL_RGB;
        break;
    case 4:
        format     = GL_RGBA8;
        sub_format = GL_RGBA;
        break;
    default:
        LOG_ERROR("Mystery channel amount {} when creating texture",
                  channel_amount);
        throw std::runtime_error{"Texture loading failed"};
    }

    glCreateTextures(GL_TEXTURE_2D, 1, &texture_id_);
    glTextureStorage2D(texture_id_, 1, format, width, height);

    glGenerateTextureMipmap(texture_id_);

    glTextureParameteri(texture_id_, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTextureParameteri(texture_id_, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTextureParameteri(texture_id_, GL_TEXTURE_MIN_FILTER,
                        GL_LINEAR_MIPMAP_LINEAR);
    glTextureParameteri(texture_id_, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    const int no_offset = 0;
    glTextureSubImage2D(texture_id_, 0, no_offset, no_offset, width, height,
                        sub_format, GL_UNSIGNED_BYTE, texture_bytes);

    stbi_image_free(texture_bytes);
}

OpenGLTexture2D::OpenGLTexture2D(const Vector3& colour,
                                 const std::uint32_t width,
                                 const std::uint32_t height)
    : texture_id_{0}, type_{Texture::Type::DIFFUSE}
{
    GLenum format     = GL_RGB8;
    GLenum sub_format = GL_RGB;

    const std::uint32_t rgb = colour_vector_to_hex(colour);

    glCreateTextures(GL_TEXTURE_2D, 1, &texture_id_);
    glTextureStorage2D(texture_id_, 1, format, width, height);

    glTextureParameteri(texture_id_, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTextureParameteri(texture_id_, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTextureParameteri(texture_id_, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTextureParameteri(texture_id_, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    const int no_offset = 0;
    glTextureSubImage2D(texture_id_, 0, no_offset, no_offset, width, height,
                        sub_format, GL_UNSIGNED_BYTE, &rgb);
}

OpenGLTexture2D::~OpenGLTexture2D()
{
    glDeleteTextures(1, &texture_id_);
}

Texture::Type OpenGLTexture2D::type() const
{
    return type_;
}

void OpenGLTexture2D::bind(const std::uint32_t slot) const
{
    glBindTextureUnit(slot, texture_id_);
}

void OpenGLTexture2D::unbind() const
{
    glBindTextureUnit(0, texture_id_);
}

bool OpenGLTexture2D::operator==(const Texture& other) const
{
    return texture_id_ ==
           (dynamic_cast<const OpenGLTexture2D&>(other)).texture_id_;
}

} // namespace SGE
