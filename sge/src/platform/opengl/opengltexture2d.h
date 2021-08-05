#ifndef _SGE_OPENGL_TEXTURE2D_H
#define _SGE_OPENGL_TEXTURE2D_H

#include "texture.h"
#include "texture2d.h"
#include "vector3.h"

#include <cstdint>
#include <string>

namespace SGE
{

class OpenGLTexture2D : public Texture2D
{
  private:
    std::uint32_t texture_id_;
    std::string path_;
    Texture::Type type_;

  public:
    OpenGLTexture2D(const std::string& path, Texture::Type type);
    OpenGLTexture2D(const Vector3& colour, std::uint32_t width,
                    std::uint32_t height);
    ~OpenGLTexture2D();

    OpenGLTexture2D(const OpenGLTexture2D&)  = delete;
    OpenGLTexture2D(const OpenGLTexture2D&&) = delete;
    OpenGLTexture2D& operator=(const OpenGLTexture2D&) = delete;
    OpenGLTexture2D& operator=(const OpenGLTexture2D&&) = delete;

    Texture::Type type() const override;

    void bind(std::uint32_t slot) const override;
    void unbind() const override;
    bool operator==(const Texture& other) const override;
};

} // namespace SGE

#endif
