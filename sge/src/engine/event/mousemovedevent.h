#ifndef _SGE_MOUSE_MOVED_EVENT_H
#define _SGE_MOUSE_MOVED_EVENT_H

#include "engine/event/event.h"

#include <utility>

namespace SGE
{

class MouseMovedEvent : public Event
{
  private:
    std::pair<float, float> position_;

  public:
    MouseMovedEvent(float x, float y);
    MouseMovedEvent(const std::pair<float, float>& position);

    float x() const;
    float y() const;
    std::pair<float, float> position() const;

    int categories() const override;
    std::string name() const override;
    EventType type() const override;

    static EventType static_type();
};

} // namespace SGE

#endif
