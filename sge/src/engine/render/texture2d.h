#ifndef _SGE_TEXTURE2D_H
#define _SGE_TEXTURE2D_H

#include "texture.h"

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
};

} // namespace SGE

#endif
