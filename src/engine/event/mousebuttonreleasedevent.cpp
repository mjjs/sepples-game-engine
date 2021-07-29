#include "event.h"
#include "mousebuttonreleasedevent.h"

#include <string>

namespace SGE {

MouseButtonReleasedEvent::MouseButtonReleasedEvent(const int key_code)
    : MouseButtonEvent{key_code}
{
}

int MouseButtonReleasedEvent::categories() const
{
    return EventCategory::MOUSE | EventCategory::INPUT | EventCategory::MOUSEBUTTON;
}

std::string MouseButtonReleasedEvent::name() const
{
    return "MouseButtonReleasedEvent";
}

EventType MouseButtonReleasedEvent::type() const
{
    return static_type();
}

EventType MouseButtonReleasedEvent::static_type()
{
    return EventType::MOUSE_BUTTON_RELEASED;
}

} // namespace SGE
