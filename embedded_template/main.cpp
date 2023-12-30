#include "stm32g4xx_hal_timebase_tim.h"
#include <chrono>

int main()
{
    if (HAL_InitTick(0) != HAL_OK)
    {
        return 1;
    }

    auto now_steady = std::chrono::steady_clock::now();

    volatile auto counts = now_steady.time_since_epoch().count();

    return 0;
}
