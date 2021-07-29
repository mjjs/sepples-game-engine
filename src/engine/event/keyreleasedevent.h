#ifndef _SGE_KEY_RELEASED_EVENT_H
#define _SGE_KEY_RELEASED_EVENT_H

#include "keyboardevent.h"
#include <string>

namespace SGE {

class KeyReleasedEvent : public KeyboardEvent {
    public:
        KeyReleasedEvent(int key_code);

    private:
        int categories() const override;
        std::string name() const override;
        EventType type() const override;

        static EventType static_type();
};

} // namespace SGE

#endif