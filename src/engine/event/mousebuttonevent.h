#ifndef _SGE_MOUSE_BUTTON_EVENT_H
#define _SGE_MOUSE_BUTTON_EVENT_H

#include "event.h"

namespace SGE {

class MouseButtonEvent : public Event {
    protected:
        int key_code_; // NOLINT
        MouseButtonEvent(int key_code);

    public:
        int key_code() const;

        int categories() const override;
        std::string name() const override;
        EventType type() const override;

        static EventType static_type();
};

} // namespace SGE

#endif
