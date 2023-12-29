#include "gettimeofday.h"
#include <chrono>

namespace
{
    using TSeconds = decltype(std::declval<timeval>().tv_sec);
    using TMicroseconds = decltype(std::declval<timeval>().tv_usec);

    static inline TSeconds seconds_passed{0};
    static inline TMicroseconds microseconds_passed{0};
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
        microseconds_passed += microseconds;

        if (microseconds_passed >= microseconds_per_second)
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
