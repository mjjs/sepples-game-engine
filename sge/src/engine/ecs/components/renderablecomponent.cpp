#include "engine/ecs/components/modelrenderercomponent.h"

#include "engine/rendering/model.h"

#include <memory>

namespace SGE
{

ModelRendererComponent::ModelRendererComponent(
    const std::shared_ptr<Model>& model)
    : model_{model}
{
}

const std::shared_ptr<Model>& ModelRendererComponent::model() const
{
    return model_;
}

std::shared_ptr<Model> ModelRendererComponent::model()
{
    return model_;
}

} // namespace SGE
