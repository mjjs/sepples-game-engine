#include "engine/event/mousemovedevent.h"

#include "engine/event/event.h"

#include <utility>

namespace SGE
{

MouseMovedEvent::MouseMovedEvent(const float x, const float y) : position_{x, y}
{
}

MouseMovedEvent::MouseMovedEvent(const std::pair<float, float>& position)
    : position_{position}
{
}

float MouseMovedEvent::x() const
{
    auto [x, _] = position();
    return x;
}

float MouseMovedEvent::y() const
{
    auto [_, y] = position();
    return y;
}

std::pair<float, float> MouseMovedEvent::position() const
{
    return position_;
}

int MouseMovedEvent::categories() const
{
    return EventCategory::INPUT | EventCategory::MOUSE;
}

std::string MouseMovedEvent::name() const
{
    return "MouseMoved";
}

EventType MouseMovedEvent::type() const
{
    return static_type();
}

EventType MouseMovedEvent::static_type()
{
    return EventType::MOUSE_MOVED;
}

} // namespace SGE
