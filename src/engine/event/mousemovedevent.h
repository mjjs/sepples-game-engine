#ifndef _SGE_MOUSE_MOVED_EVENT_H
#define _SGE_MOUSE_MOVED_EVENT_H

#include "event.h"
#include "vector2.h"

namespace SGE {

class MouseMovedEvent : public Event {
    private:
        Vector2 position_;

    public:
        MouseMovedEvent(const Vector2& position);

        float x() const;
        float y() const;
        Vector2 position() const;

        int categories() const override;
        std::string name() const override;
        EventType type() const override;

        static EventType static_type();

};

} // namespace SGE

#endif
