#ifndef _SGE_LOG_H
#define _SGE_LOG_H

#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/spdlog.h"

#include <memory>

namespace SGE
{

class Log
{
  private:
    // NOLINTNEXTLINE(cppcoreguidelines-avoid-non-const-global-variables)
    static std::shared_ptr<spdlog::logger> logger_;

  public:
    static void init();

    static std::shared_ptr<spdlog::logger>& logger();
};

} // namespace SGE

#define LOG_TRACE(...) ::SGE::Log::logger()->trace(__VA_ARGS__) // NOLINT
#define LOG_INFO(...) ::SGE::Log::logger()->info(__VA_ARGS__)   // NOLINT
#define LOG_WARN(...) ::SGE::Log::logger()->warn(__VA_ARGS__)   // NOLINT
#define LOG_ERROR(...) ::SGE::Log::logger()->error(__VA_ARGS__) // NOLINT
#define LOG_FATAL(...) ::SGE::Log::logger()->fatal(__VA_ARGS__) // NOLINT

#endif
