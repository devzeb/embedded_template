#include "stm32g4xx_hal_timebase_tim.h"
#include <chrono>

int main()
{
    // initialize timer 6 to update every 1ms and then call EmebeddedTemplate::on_millisecond_passed() of file gettimeofday.cpp
    if (embedded_template_HAL_InitTick(0) != HAL_OK)
    {
        return 1;
    }


    while (true)
    {
        auto now_steady = std::chrono::steady_clock::now();
        volatile auto seconds = std::chrono::duration_cast<std::chrono::seconds>(now_steady.time_since_epoch()).count();
        volatile int a = 0;
    }


    return 0;
}
