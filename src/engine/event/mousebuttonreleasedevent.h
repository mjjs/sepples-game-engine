#ifndef _SGE_MOUSE_BUTTON_RELEASED_EVENT_H
#define _SGE_MOUSE_BUTTON_RELEASED_EVENT_H

#include "event.h"
#include "mousebuttonevent.h"

namespace SGE {

class MouseButtonReleasedEvent : public MouseButtonEvent {
    public:
        MouseButtonReleasedEvent(int key_code);

        int categories() const override;
        std::string name() const override;
        EventType type() const override;

        static EventType static_type();
};

} // namespace SGE

#endif
