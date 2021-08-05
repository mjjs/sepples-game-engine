#ifndef _SGE_TEXTURE2D_H
#define _SGE_TEXTURE2D_H

#include "texture.h"
#include "vector3.h"

#include <cstdint>
#include <memory>
#include <string>

namespace SGE
{

class Texture2D : public Texture
{
  public:
    static std::shared_ptr<Texture2D> create(const std::string& path,
                                             Type type);

    static std::shared_ptr<Texture2D> create(const Vector3& colour,
                                             std::uint32_t width,
                                             std::uint32_t height);
};

} // namespace SGE

#endif
