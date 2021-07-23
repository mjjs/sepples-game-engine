#include "gamecomponent.h"
#include "gameobject.h"
#include "transform.h"

namespace SGE {
void GameComponent::init()
{
}

void GameComponent::update([[maybe_unused]] float delta)
{
}

void GameComponent::fixed_update([[maybe_unused]] const Transform& transform)
{
}

void GameComponent::render(
        [[maybe_unused]] const Transform& transform,
        [[maybe_unused]] Shader& shader,
        [[maybe_unused]] const RenderingEngine& rendering_engine
        )
{
}

void GameComponent::add_to_rendering_engine(
        [[maybe_unused]] RenderingEngine& rendering_engine)
{
}

Transform& GameComponent::get_transform() const
{
    return parent_->transform();
}

void GameComponent::set_parent(GameObject* game_object)
{
    parent_ = game_object;
}

} // namespace SGE
