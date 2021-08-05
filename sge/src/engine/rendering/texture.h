#ifndef _SGE_TEXTURE_H
#define _SGE_TEXTURE_H

#include <cstdint>

namespace SGE
{

class Texture
{
  public:
    enum class Type { DIFFUSE, SPECULAR, NORMAL };

    Texture()          = default;
    virtual ~Texture() = default;

    Texture(const Texture&)  = delete;
    Texture(const Texture&&) = delete;
    Texture& operator=(const Texture&) = delete;
    Texture& operator=(const Texture&&) = delete;

    virtual Type type() const                           = 0;
    virtual void bind(std::uint32_t slot = 0) const     = 0;
    virtual void unbind() const                         = 0;
    virtual bool operator==(const Texture& other) const = 0;
};

} // namespace SGE

#endif
