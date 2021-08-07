#ifndef _SGE_PROFILER_H
#define _SGE_PROFILER_H

#ifdef SGE_ENABLE_PROFILING

#include <algorithm>
#include <chrono>
#include <cstdint>
#include <fstream>
#include <functional>
#include <iostream>
#include <string>
#include <thread>

namespace SGE
{

struct ProfileResult {
    std::string name;
    unsigned long long start;
    unsigned long long end;
    std::uint32_t thread_id;
};

class Profiler
{
  private:
    unsigned int profile_count_{0};

    std::ofstream output_stream_;

  public:
    void start(const std::string& output_file = "profiler.json")
    {
        output_stream_.open(output_file);
        write_profiler_header();
    }

    void stop()
    {
        write_profiler_footer();
        profile_count_ = 0;
        output_stream_.close();
    }

    void write_profile(const ProfileResult& result)
    {
        if (profile_count_++ > 0) {
            output_stream_ << ",";
        }

        std::string name = result.name;
        std::replace(name.begin(), name.end(), '"', '\'');

        output_stream_ << "{";
        output_stream_ << "\"cat\":\"function\",";
        output_stream_ << "\"dur\":" << (result.end - result.start) << ',';
        output_stream_ << "\"name\":\"" << name << "\",";
        output_stream_ << "\"ph\":\"X\",";
        output_stream_ << "\"pid\":0,";
        output_stream_ << "\"tid\":" << result.thread_id << ",";
        output_stream_ << "\"ts\":" << result.start;
        output_stream_ << "}";

        output_stream_.flush();
    }

    void write_profiler_header()
    {
        output_stream_ << R"({"otherData": {}, "traceEvents": [)";
    }

    void write_profiler_footer()
    {
        output_stream_ << "]}";
        output_stream_.flush();
    }

    static Profiler& get()
    {
        static Profiler instance;
        return instance;
    }
};

class ProfilingTimer
{
  private:
    const char* name_;
    std::chrono::time_point<std::chrono::high_resolution_clock> timer_start_;
    bool running_;

  public:
    ProfilingTimer(const char* name)
        : name_{name}, timer_start_{std::chrono::high_resolution_clock::now()},
          running_{true}
    {
    }

    ~ProfilingTimer()
    {
        if (running_) {
            stop();
        }
    }

    void stop()
    {
        auto end_time = std::chrono::high_resolution_clock::now();

        unsigned long long start =
            std::chrono::time_point_cast<std::chrono::microseconds>(
                timer_start_)
                .time_since_epoch()
                .count();

        unsigned long long end =
            std::chrono::time_point_cast<std::chrono::microseconds>(end_time)
                .time_since_epoch()
                .count();

        std::uint32_t thread_id =
            std::hash<std::thread::id>{}(std::this_thread::get_id());

        Profiler::get().write_profile({name_, start, end, thread_id});

        running_ = false;
    }

    ProfilingTimer(const ProfilingTimer&)  = delete;
    ProfilingTimer(const ProfilingTimer&&) = delete;
    ProfilingTimer& operator=(const ProfilingTimer&) = delete;
    ProfilingTimer& operator=(const ProfilingTimer&&) = delete;
};

} // namespace SGE

// NOLINTNEXTLINE
#define SGE_PROFILER_START(filepath) ::SGE::Profiler::get().start(filepath)
  // NOLINTNEXTLINE
#define SGE_PROFILER_STOP() ::SGE::Profiler::get().stop()
  // NOLINTNEXTLINE
#define SGE_PROFILE_SCOPE(name) ::SGE::ProfilingTimer timer##__LINE__(name);
  // NOLINTNEXTLINE
#define SGE_PROFILE_FUNCTION()                                                 \
    SGE_PROFILE_SCOPE(static_cast<const char*>(__PRETTY_FUNCTION__))
#else
#define SGE_PROFILER_START(filepath)
#define SGE_PROFILER_STOP()
#define SGE_PROFILE_SCOPE(name)
#define SGE_PROFILE_FUNCTION()
#endif

#endif
