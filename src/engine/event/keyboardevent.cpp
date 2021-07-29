#include "event.h"
#include "keyboardevent.h"

#include <string>

namespace SGE {

KeyboardEvent::KeyboardEvent(const int key_code)
    : key_code_{key_code}
{
}

int KeyboardEvent::key_code() const
{ return key_code_;
}

int KeyboardEvent::categories() const
{
    return EventCategory::KEYBOARD | EventCategory::INPUT;
}

std::string KeyboardEvent::name() const
{
    return "KeyboardEvent";
}

EventType KeyboardEvent::type() const
{
    return static_type();
}

EventType KeyboardEvent::static_type()
{
    // Base class, this is not supposed to be instantiated.
    return EventType::NONE;
}

} // namespace SGE
