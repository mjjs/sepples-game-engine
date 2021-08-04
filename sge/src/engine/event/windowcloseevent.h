#ifndef _SGE_WINDOW_CLOSE_EVENT_H
#define _SGE_WINDOW_CLOSE_EVENT_H

#include "event.h"

#include <string>

namespace SGE
{

class WindowCloseEvent : public Event
{
  public:
    int categories() const override;
    std::string name() const override;
    EventType type() const override;

    static EventType static_type();
};

} // namespace SGE

#endif
