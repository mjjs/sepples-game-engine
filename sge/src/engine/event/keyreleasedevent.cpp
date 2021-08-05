#include "engine/event/keyreleasedevent.h"

namespace SGE {

KeyReleasedEvent::KeyReleasedEvent(const SDL_Keycode key_code)
    : KeyboardEvent{key_code}
{
}

int KeyReleasedEvent::categories() const
{
    return EventCategory::KEYBOARD | EventCategory::INPUT;
}

std::string KeyReleasedEvent::name() const
{
    return "KeyReleasedEvent";
}

EventType KeyReleasedEvent::type() const
{
    return static_type();
}

EventType KeyReleasedEvent::static_type()
{
    return EventType::KEY_RELEASED;
}

} // namespace SGE
