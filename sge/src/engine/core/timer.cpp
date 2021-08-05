#include "engine/core/timer.h"

namespace SGE {

const int MS_PER_SECOND = 1000;

void Timer::update_times()
{
    auto current_time = std::chrono::steady_clock::now();
    auto elapsed_time =
        std::chrono::duration_cast<std::chrono::milliseconds>(current_time - previous_time_);

    previous_time_ = current_time;
    delta_ = elapsed_time.count();

    float elapsed_seconds = static_cast<float>(elapsed_time.count()) / MS_PER_SECOND;
    unprocessed_time_ += elapsed_seconds;
    seconds_spent_this_frame_ += elapsed_seconds;
}

void Timer::start_timer()
{
    previous_time_ = std::chrono::steady_clock::now();
}

void Timer::use_unprocessed_time()
{
    unprocessed_time_ -= fixed_time_step_;
}

void Timer::reset_seconds_spent_this_frame()
{
    seconds_spent_this_frame_ = 0.0F;
}

bool Timer::game_needs_updating() const
{
    return unprocessed_time_ >= fixed_time_step_;
}

bool Timer::has_second_passed() const
{
    return seconds_spent_this_frame_ >= 1.0F;
}

float Timer::unprocessed_time() const
{
    return unprocessed_time_;
}

float Timer::fixed_time_step() const
{
    return fixed_time_step_;
}

float Timer::delta() const
{
    return delta_;
}

} // namespace SGE
