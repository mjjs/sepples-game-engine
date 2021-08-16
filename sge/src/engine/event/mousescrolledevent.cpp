#include "engine/event/mousescrolledevent.h"

#include "engine/event/event.h"

#include <string>

namespace SGE
{

MouseScrolledEvent::MouseScrolledEvent(const float x, const float y)
    : offsets_{x, y}
{
}

MouseScrolledEvent::MouseScrolledEvent(const std::pair<float, float>& offsets)
    : offsets_{offsets}
{
}

float MouseScrolledEvent::x_offset() const
{
    auto [x, _] = offsets();
    return x;
}

float MouseScrolledEvent::y_offset() const
{
    auto [_, y] = offsets();
    return y;
}

std::pair<float, float> MouseScrolledEvent::offsets() const
{
    return offsets_;
}

int MouseScrolledEvent::categories() const
{
    return EventCategory::MOUSE | EventCategory::INPUT |
           EventCategory::MOUSEBUTTON;
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
