#include "gamecomponent.h"
#include "gameobject.h"
#include "transform.h"

void SGE::GameComponent::init()
{
}

void SGE::GameComponent::input(
        [[maybe_unused]] const Input& input,
        [[maybe_unused]] const Math::Transform& transform
        )
{
}

void SGE::GameComponent::update(
        [[maybe_unused]] const Math::Transform& transform,
        [[maybe_unused]] float delta
        )
{
}

void SGE::GameComponent::fixed_update([[maybe_unused]] const Math::Transform& transform)
{
}

void SGE::GameComponent::render(
        [[maybe_unused]] const Math::Transform& transform,
        [[maybe_unused]] Shader& shader,
        [[maybe_unused]] const RenderingEngine& rendering_engine
        )
{
}

void SGE::GameComponent::add_to_rendering_engine(
        [[maybe_unused]] RenderingEngine& rendering_engine)
{
}


void SGE::GameComponent::set_parent(SGE::GameObject* game_object)
{
    parent_ = game_object;
}

Math::Transform& SGE::GameComponent::get_transform()
{
    return parent_->transform();
}
