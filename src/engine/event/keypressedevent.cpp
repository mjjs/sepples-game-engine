#include "keypressedevent.h"

namespace SGE {

KeyPressedEvent::KeyPressedEvent(const SDL_Keycode key_code)
    : KeyboardEvent{key_code}
{
}

int KeyPressedEvent::categories() const
{
    return EventCategory::KEYBOARD | EventCategory::INPUT;
}

std::string KeyPressedEvent::name() const
{
    return "KeyPressedEvent";
}

EventType KeyPressedEvent::type() const
{
    return static_type();
}

EventType KeyPressedEvent::static_type()
{
    return EventType::KEY_PRESSED;
}

} // namespace SGE
