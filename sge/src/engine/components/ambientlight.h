#ifndef _SGE_AMBIENTLIGHT_H
#define _SGE_AMBIENTLIGHT_H

#include "engine/components/light.h"
#include "engine/math/vector3.h"

namespace SGE
{
class AmbientLight : public Light
{
  private:
    Vector3 direction_;

  public:
    AmbientLight();
    explicit AmbientLight(float intensity);
};
} // namespace SGE

#endif
