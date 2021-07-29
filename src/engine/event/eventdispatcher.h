#ifndef _SGE_EVENT_DISPATCHER_H
#define _SGE_EVENT_DISPATCHER_H

namespace SGE {

class Event;

class EventDispatcher {
    private:
        Event& event_;

    public:
        EventDispatcher(Event& event);

        template<typename T, typename F>
        bool dispatch(const F& event_handler);
};

} // namespace SGE

#endif
