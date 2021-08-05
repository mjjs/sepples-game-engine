#ifndef _SGE_WINDOW_RESIZE_EVENT_H
#define _SGE_WINDOW_RESIZE_EVENT_H

#include "engine/event/event.h"
#include "engine/math/vector2.h"

#include <string>

namespace SGE
{

class WindowResizeEvent : public Event
{
  private:
    unsigned int width_;
    unsigned int height_;

  public:
    WindowResizeEvent(unsigned int width, unsigned int height);

    unsigned int width() const;
    unsigned int height() const;

    int categories() const override;
    std::string name() const override;
    EventType type() const override;

    static EventType static_type();
};

} // namespace SGE

#endif
