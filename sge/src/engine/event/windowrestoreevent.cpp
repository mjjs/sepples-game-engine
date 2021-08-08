#include "engine/event/windowrestoreevent.h"

#include "engine/event/event.h"

#include <string>

namespace SGE
{

int WindowRestoreEvent::categories() const
{
    return EventCategory::WINDOW;
}

std::string WindowRestoreEvent::name() const
{
    return "WindowRestoreEvent";
}

EventType WindowRestoreEvent::type() const
{
    return static_type();
}

EventType WindowRestoreEvent::static_type()
{
    return EventType::WINDOW_RESTORE;
}

} // namespace SGE
