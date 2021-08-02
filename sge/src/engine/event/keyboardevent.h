#ifndef _SGE_KEYBOARD_EVENT_H
#define _SGE_KEYBOARD_EVENT_H

#include "event.h"
#include <SDL2/SDL_keycode.h>
#include <string>

namespace SGE {

class KeyboardEvent : public Event {
    protected:
        SDL_Keycode key_code_; // NOLINT
        KeyboardEvent(SDL_Keycode key_code);

    public:
        SDL_Keycode key_code() const;

        int categories() const override;
        std::string name() const override;
        EventType type() const override;

        static EventType static_type();
};

} // namespace SGE

#endif
