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
        inline void start_timer()
        {
            previous_time_ = std::chrono::steady_clock::now();
        }

        inline void use_unprocessed_time()
        {
            unprocessed_time_ -= fixed_time_step_;
        }

        inline void reset_seconds_spent_this_frame()
        {
            seconds_spent_this_frame_ = 0.0F;
        }

        inline bool game_needs_updating() const
        {
            return unprocessed_time_ >= fixed_time_step_;
        }

        inline bool has_second_passed() const
        {
            return seconds_spent_this_frame_ >= 1.0F;
        }

        inline float unprocessed_time() const
        {
            return unprocessed_time_;
        }

        inline float fixed_time_step() const
        {
            return fixed_time_step_;
        }

        inline float delta() const
        {
            return delta_;
        }
};

} // namespace SGE
#endif
