#include "log.h"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"

#include <memory>

namespace SGE {

// NOLINTNEXTLINE(cppcoreguidelines-avoid-non-const-global-variables)
std::shared_ptr<spdlog::logger> Log::logger_{};

void Log::init()
{
    spdlog::set_pattern("%^[%T] %n: %v%$");

    logger_ = spdlog::stdout_color_mt("SGE");
    logger_->set_level(spdlog::level::trace);
}

std::shared_ptr<spdlog::logger>& Log::logger()
{
    return logger_;
}

} // namespace SGE
