#ifndef _SGE_LOG_H
#define _SGE_LOG_H

#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"

#include <memory>

namespace SGE {

class Log {
private:
    // NOLINTNEXTLINE(cppcoreguidelines-avoid-non-const-global-variables)
    static std::shared_ptr<spdlog::logger> engine_logger_;
    // NOLINTNEXTLINE(cppcoreguidelines-avoid-non-const-global-variables)
    static std::shared_ptr<spdlog::logger> game_logger_;

public:
    static void init();

    static std::shared_ptr<spdlog::logger>& engine_logger();
    static std::shared_ptr<spdlog::logger>& game_logger();

};

} // namespace SGE

#define ENGINE_LOG_TRACE(...) ::SGE::Log::engine_logger()->trace(__VA_ARGS__) // NOLINT
#define ENGINE_LOG_INFO(...) ::SGE::Log::engine_logger()->info(__VA_ARGS__) // NOLINT
#define ENGINE_LOG_WARN(...) ::SGE::Log::engine_logger()->warn(__VA_ARGS__) // NOLINT
#define ENGINE_LOG_ERROR(...) ::SGE::Log::engine_logger()->error(__VA_ARGS__) // NOLINT
#define ENGINE_LOG_FATAL(...) ::SGE::Log::engine_logger()->fatal(__VA_ARGS__) // NOLINT

#define LOG_TRACE(...) ::SGE::Log::game_logger()->trace(__VA_ARGS__) // NOLINT
#define LOG_INFO(...) ::SGE::Log::game_logger()->info(__VA_ARGS__) // NOLINT
#define LOG_WARN(...) ::SGE::Log::game_logger()->warn(__VA_ARGS__) // NOLINT
#define LOG_ERROR(...) ::SGE::Log::game_logger()->error(__VA_ARGS__) // NOLINT
#define LOG_FATAL(...) ::SGE::Log::game_logger()->fatal(__VA_ARGS__) // NOLINT

#endif
