#include "gamecomponent.h"
#include "gameobject.h"
#include "transform.h"

namespace SGE {
void GameComponent::init()
{
}

void GameComponent::update(
        [[maybe_unused]] const Math::Transform& transform,
        [[maybe_unused]] float delta
        )
{
}

void GameComponent::fixed_update([[maybe_unused]] const Math::Transform& transform)
{
}

void GameComponent::render(
        [[maybe_unused]] const Math::Transform& transform,
        [[maybe_unused]] Shader& shader,
        [[maybe_unused]] const RenderingEngine& rendering_engine
        )
{
}

void GameComponent::add_to_rendering_engine(
        [[maybe_unused]] RenderingEngine& rendering_engine)
{
}

Math::Transform& GameComponent::get_transform()
{
    return parent_->transform();
}

} // namespace SGE
