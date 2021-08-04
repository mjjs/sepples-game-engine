#ifndef _SGE_EVENT_H
#define _SGE_EVENT_H

#include <functional>
#include <string>

#define BIND_EVENT_FN(fn)                                                      \
    [this](auto&&... args) -> decltype(auto) {                                 \
        return this->fn(std::forward<decltype(args)>(args)...);                \
    }

namespace SGE
{

constexpr int bit(int x)
{
    return 1 << x;
}

enum class EventType {
    NONE,
    WINDOW_CLOSE,
    WINDOW_RESIZE,
    KEY_PRESSED,
    KEY_RELEASED,
    MOUSE_BUTTON_PRESSED,
    MOUSE_BUTTON_RELEASED,
    MOUSE_MOVED,
    MOUSE_SCROLLED,
};

enum EventCategory {
    NONE        = 0,
    WINDOW      = bit(0),
    INPUT       = bit(1),
    KEYBOARD    = bit(2),
    MOUSE       = bit(3),
    MOUSEBUTTON = bit(4),
};

class Event
{
  public:
    Event()          = default;
    virtual ~Event() = default;

    Event(const Event&)  = delete;
    Event(const Event&&) = delete;
    Event& operator=(const Event&) = delete;
    Event& operator=(const Event&&) = delete;

    bool handled = false;

    virtual EventType type() const   = 0;
    virtual std::string name() const = 0;
    virtual int categories() const   = 0;

    bool is_in_category(EventCategory category) const
    {
        return (categories() & category) != 0;
    }
};

using EventCallbackFn = std::function<void(Event&)>;

} // namespace SGE

#endif
