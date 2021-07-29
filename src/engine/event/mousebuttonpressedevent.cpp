#include "event.h"
#include "mousebuttonpressedevent.h"

#include <string>

namespace SGE {

MouseButtonPressedEvent::MouseButtonPressedEvent(const int key_code)
    : MouseButtonEvent{key_code}
{
}

int MouseButtonPressedEvent::categories() const
{
    return EventCategory::MOUSE | EventCategory::INPUT | EventCategory::MOUSEBUTTON;
}

std::string MouseButtonPressedEvent::name() const
{
    return "MouseButtonPressedEvent";
}

EventType MouseButtonPressedEvent::type() const
{
    return static_type();
}

EventType MouseButtonPressedEvent::static_type()
{
    return EventType::MOUSE_BUTTON_PRESSED;
}

} // namespace SGE
