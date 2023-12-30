#ifndef STM32G4XX_HAL_TIMEBASE_TIM_H
#define STM32G4XX_HAL_TIMEBASE_TIM_H

#include <cstdint>
#include <stm32g4xx_hal_def.h>

extern "C" {
HAL_StatusTypeDef HAL_InitTick(uint32_t TickPriority);
}

#endif //STM32G4XX_HAL_TIMEBASE_TIM_H
