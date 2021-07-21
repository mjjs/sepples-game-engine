#include "timer.h"

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

} // namespace SGE
