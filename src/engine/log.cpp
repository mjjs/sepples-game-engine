#include "log.h"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"

#include <memory>

// NOLINTNEXTLINE(cppcoreguidelines-avoid-non-const-global-variables)
std::shared_ptr<spdlog::logger> SGE::Log::engine_logger_{};
// NOLINTNEXTLINE(cppcoreguidelines-avoid-non-const-global-variables)
std::shared_ptr<spdlog::logger> SGE::Log::game_logger_{};

void SGE::Log::init()
{
    spdlog::set_pattern("%^[%T] %n: %v%$");

    engine_logger_ = spdlog::stdout_color_mt("ENGINE");
    engine_logger_->set_level(spdlog::level::trace);

    game_logger_ = spdlog::stdout_color_mt("GAME");
    game_logger_->set_level(spdlog::level::trace);
}
