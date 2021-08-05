#include "engine/event/event.h"
#include "engine/event/windowcloseevent.h"

#include <string>

namespace SGE {

int WindowCloseEvent::categories() const
{
    return EventCategory::WINDOW;
}

std::string WindowCloseEvent::name() const
{
    return "WindowCloseEvent";
}

EventType WindowCloseEvent::type() const
{
    return static_type();
}

EventType WindowCloseEvent::static_type()
{
    return EventType::WINDOW_CLOSE;
}

} // namespace SGE
