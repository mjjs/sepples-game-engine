#ifndef _SGE_MOUSE_BUTTON_PRESSED_EVENT_H
#define _SGE_MOUSE_BUTTON_PRESSED_EVENT_H

#include "event.h"
#include "mousebuttonevent.h"

#include <cstdint>

namespace SGE
{

class MouseButtonPressedEvent : public MouseButtonEvent
{
  public:
    MouseButtonPressedEvent(std::uint8_t key_code);

    int categories() const override;
    std::string name() const override;
    EventType type() const override;

    static EventType static_type();
};

} // namespace SGE

#endif
