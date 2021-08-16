#ifndef _SGE_MOUSE_SCROLLED_EVENT_H
#define _SGE_MOUSE_SCROLLED_EVENT_H

#include "engine/event/event.h"

#include <string>
#include <utility>

namespace SGE
{

class MouseScrolledEvent : public Event
{
  private:
    std::pair<float, float> offsets_;

  public:
    MouseScrolledEvent(float x, float y);
    MouseScrolledEvent(const std::pair<float, float>& offsets);

    float x_offset() const;
    float y_offset() const;
    std::pair<float, float> offsets() const;

    int categories() const override;
    std::string name() const override;
    EventType type() const override;

    static EventType static_type();
};

} // namespace SGE

#endif
