#include "gamecomponent.h"
#include "gameobject.h"
#include "transform.h"

void SGE::GameComponent::init() {};
void SGE::GameComponent::input(const Input& input, const Math::Transform& transform) {};
void SGE::GameComponent::update(const Math::Transform& transform, float delta) {};
void SGE::GameComponent::fixed_update(const Math::Transform& transform) {};
void SGE::GameComponent::render(const Math::Transform& transform, Shader& shader, const RenderingEngine& rendering_engine) {};
void SGE::GameComponent::add_to_rendering_engine(RenderingEngine& rendering_engine) {};

void SGE::GameComponent::set_parent(SGE::GameObject* game_object)
{
    parent_ = game_object;
}

Math::Transform& SGE::GameComponent::get_transform()
{
    return parent_->transform();
}
