#ifndef _SGE_MODEL_RENDERER_COMPONENT_H
#define _SGE_MODEL_RENDERER_COMPONENT_H

#include "engine/rendering/model.h"

#include <memory>

namespace SGE
{

class ModelRendererComponent
{
  private:
    std::shared_ptr<Model> model_;

  public:
    ModelRendererComponent() = default;
    ModelRendererComponent(const std::shared_ptr<Model>& model);

    const std::shared_ptr<Model>& model() const;
    std::shared_ptr<Model> model();
};

} // namespace SGE

#endif
