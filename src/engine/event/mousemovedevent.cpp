#include "event.h"
#include "mousemovedevent.h"
#include "vector2.h"

namespace SGE {

MouseMovedEvent::MouseMovedEvent(const Vector2& position)
    : position_{position}
{
}

float MouseMovedEvent::x() const
{
    return position_.x;
}

float MouseMovedEvent::y() const
{
    return position_.y;
}

Vector2 MouseMovedEvent::position() const
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
