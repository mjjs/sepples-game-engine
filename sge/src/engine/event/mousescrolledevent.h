#ifndef _SGE_MOUSE_SCROLLED_EVENT_H
#define _SGE_MOUSE_SCROLLED_EVENT_H

#include "engine/event/event.h"
#include "engine/math/vector2.h"

#include <string>

namespace SGE
{

class MouseScrolledEvent : public Event
{
  private:
    Vector2 offsets_;

  public:
    MouseScrolledEvent(const Vector2& offsets);

    float x_offset() const;
    float y_offset() const;
    Vector2 offsets() const;

    int categories() const override;
    std::string name() const override;
    EventType type() const override;

    static EventType static_type();
};

} // namespace SGE

#endif
