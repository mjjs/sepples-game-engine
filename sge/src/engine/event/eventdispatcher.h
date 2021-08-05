#ifndef _SGE_EVENT_DISPATCHER_H
#define _SGE_EVENT_DISPATCHER_H

#include "engine/event/event.h"

namespace SGE
{

class EventDispatcher
{
  private:
    Event& event_;

  public:
    EventDispatcher(Event& event) : event_{event}
    {
    }

    template <typename T, typename F> bool dispatch(const F& event_handler)
    {
        if (event_.type() == T::static_type()) {
            event_.handled |= event_handler(static_cast<T&>(event_));
            return true;
        }

        return false;
    }
};

} // namespace SGE

#endif
