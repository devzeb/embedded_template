#include "gettimeofday.h"
#include <chrono>
#include <atomic>

namespace
{
    // using TSeconds = decltype(std::declval<timeval>().tv_sec);
    // not using decltype because it's internally a long long (int64_t), which is not compatible with std::atomic on the cortex m platform
    using TSeconds = std::uint32_t; //  4294967295 seconds = 136,1 years -> max uptime of 136 years is enough
    using TMicroseconds = decltype(std::declval<timeval>().tv_usec);

    // updated from the timer interrupt, so the variables need to be atomic
    inline std::atomic<TSeconds> seconds_passed{0};
    inline std::atomic<TMicroseconds> microseconds_passed{0};
}


extern "C" {
    int _gettimeofday(timeval* ptimeval,
                      [[maybe_unused]] void* ptimezone)
    {
        ptimeval->tv_sec = seconds_passed;
        ptimeval->tv_usec = microseconds_passed;
        return 0;
    }
}

namespace EmbeddedTemplate
{
    void on_microseconds_passed(const TMicroseconds microseconds)
    {
        static constexpr auto microseconds_per_second = 1000 * 1000;

        // use a non atomic variable to store the result, because re-reading the atomic variable later in the
        // if statement is more expensive
        const auto result = microseconds_passed += microseconds;

        if (result >= microseconds_per_second)
        {
            seconds_passed += 1;
            microseconds_passed -= microseconds_per_second;
        }
    }

    void on_millisecond_passed()
    {
        on_microseconds_passed(1000);
    }

    void on_microsecond_passed()
    {
        on_microseconds_passed(1);
    }
} // namespace EmbeddedTemplate
