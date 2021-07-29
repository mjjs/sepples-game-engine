#include "event.h"
#include "mousescrolledevent.h"
#include "vector2.h"

#include <string>

namespace SGE {

MouseScrolledEvent::MouseScrolledEvent(const Vector2& offsets)
    : offsets_{offsets}
{
}

float MouseScrolledEvent::x_offset() const
{
    return offsets_.x;
}

float MouseScrolledEvent::y_offset() const
{
    return offsets_.y;
}

Vector2 MouseScrolledEvent::offsets() const
{
    return offsets_;
}

int MouseScrolledEvent::categories() const
{
    return EventCategory::MOUSE | EventCategory::INPUT | EventCategory::MOUSEBUTTON;
}

EventType MouseScrolledEvent::type() const
{
    return static_type();
}

EventType MouseScrolledEvent::static_type()
{
    return EventType::MOUSE_SCROLLED;
}

std::string MouseScrolledEvent::name() const
{
    return "MouseScrolledEvent";
}

} // namespace SGE
