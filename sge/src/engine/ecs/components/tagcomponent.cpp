#include "engine/ecs/components/tagcomponent.h"

#include <string>

namespace SGE
{

TagComponent::TagComponent(const std::string& tag) : tag_{tag}
{
}

const std::string& TagComponent::tag() const
{
    return tag_;
}

} // namespace SGE
