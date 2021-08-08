#include "engine/event/windowminimizeevent.h"

#include "engine/event/event.h"

#include <string>

namespace SGE
{

int WindowMinimizeEvent::categories() const
{
    return EventCategory::WINDOW;
}

std::string WindowMinimizeEvent::name() const
{
    return "WindowMinimizeEvent";
}

EventType WindowMinimizeEvent::type() const
{
    return static_type();
}

EventType WindowMinimizeEvent::static_type()
{
    return EventType::WINDOW_MINIMIZE;
}

} // namespace SGE
