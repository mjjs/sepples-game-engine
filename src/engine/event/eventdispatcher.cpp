#include "eventdispatcher.h"
#include "event.h"

namespace SGE {

EventDispatcher::EventDispatcher(Event& event)
    : event_{event}
{
}

template<typename T, typename F>
bool EventDispatcher::dispatch(const F& event_handler)
{
    if (event_.type() == T::static_type()) {
        event_.handled |= event_handler(static_cast<T&>(event_));
        return true;
    }

    return false;
}

} // namespace SGE
