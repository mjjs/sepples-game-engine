#ifndef _SGE_KEYBOARD_EVENT_H
#define _SGE_KEYBOARD_EVENT_H

#include "event.h"
#include <string>

namespace SGE {

class KeyboardEvent : public Event {
    protected:
        int key_code_; // NOLINT
        KeyboardEvent(int key_code);

    public:
        int key_code() const;

        int categories() const override;
        std::string name() const override;
        EventType type() const override;

        static EventType static_type();
};

} // namespace SGE

#endif
