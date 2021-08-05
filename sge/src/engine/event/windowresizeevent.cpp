#include "engine/event/event.h"
#include "engine/math/vector2.h"
#include "engine/event/windowresizeevent.h"

#include <string>

namespace SGE {

WindowResizeEvent::WindowResizeEvent(const unsigned int width, const unsigned int height)
    : width_{width}, height_{height}
{
}

unsigned int WindowResizeEvent::width() const
{
    return width_;
}

unsigned int WindowResizeEvent::height() const
{
    return height_;
}

int WindowResizeEvent::categories() const
{
    return EventCategory::WINDOW;
}

std::string WindowResizeEvent::name() const
{
    return "WindowResizeEvent";
}

EventType WindowResizeEvent::type() const
{
    return static_type();
}

EventType WindowResizeEvent::static_type()
{
    return EventType::WINDOW_RESIZE;
}

} // namespace SGE
