#ifndef _SGE_TIME_H
#define _SGE_TIME_H

#include <chrono>

namespace SGE {

class Engine;

class Timer {
    friend class Engine;

    private:
        const float fixed_time_step_ = 0.01F;
        float seconds_spent_this_frame_ = 0.0F;
        float unprocessed_time_ = 0.0F;
        std::chrono::time_point<std::chrono::steady_clock> previous_time_{};
        float delta_ = 0;
        void update_times();

    public:
        void start_timer();
        void use_unprocessed_time();
        void reset_seconds_spent_this_frame();
        bool game_needs_updating() const;
        bool has_second_passed() const;
        float unprocessed_time() const;
        float fixed_time_step() const;
        float delta() const;
};

} // namespace SGE
#endif
