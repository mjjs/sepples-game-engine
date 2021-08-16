#ifndef _SGE_TEXTURE2D_H
#define _SGE_TEXTURE2D_H

#include "engine/rendering/texture.h"

#include <cstdint>
#include <glm/glm.hpp>
#include <memory>
#include <string>

namespace SGE
{

class Texture2D : public Texture
{
  public:
    static std::shared_ptr<Texture2D> create(const std::string& path,
                                             Type type);

    static std::shared_ptr<Texture2D> create(const glm::vec4& colour,
                                             std::uint32_t width,
                                             std::uint32_t height);
};

} // namespace SGE

#endif
