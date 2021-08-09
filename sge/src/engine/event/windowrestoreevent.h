#ifndef _SGE_WINDOW_RESTORE_EVENT_H
#define _SGE_WINDOW_RESTORE_EVENT_H

#include "engine/event/event.h"

#include <string>

namespace SGE
{

class WindowRestoreEvent : public Event
{
  public:
    int categories() const override;
    std::string name() const override;
    EventType type() const override;

    static EventType static_type();
};

} // namespace SGE

#endif