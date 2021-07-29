#include "event.h"
#include "mousebuttonevent.h"

#include <string>

namespace SGE {

MouseButtonEvent::MouseButtonEvent(const int key_code)
    : key_code_{key_code}
{
}

int MouseButtonEvent::key_code() const
{
    return key_code_;
}

int MouseButtonEvent::categories() const
{
    return EventCategory::MOUSE | EventCategory::INPUT | EventCategory::MOUSEBUTTON;
}

std::string MouseButtonEvent::name() const
{
    return "MouseButtonEvent";
}

EventType MouseButtonEvent::type() const
{
    return static_type();
}

EventType MouseButtonEvent::static_type()
{
    // Base class, this is not supposed to be instantiated.
    return EventType::NONE;
}

} // namespace SGE
