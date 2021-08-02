#ifndef _SGE_KEY_PRESSED_EVENT_H
#define _SGE_KEY_PRESSED_EVENT_H

#include "keyboardevent.h"

#include <string>

namespace SGE {

class KeyPressedEvent : public KeyboardEvent {
    public:
        KeyPressedEvent(SDL_Keycode key_code);

        int categories() const override;
        std::string name() const override;
        EventType type() const override;

        static EventType static_type();
};

} // namespace SGE

#endif
