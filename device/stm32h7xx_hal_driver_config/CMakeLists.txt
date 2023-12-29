add_library(stm32h7xx_hal_driver_config INTERFACE)
add_library(embedded_template::stm32h7xx_hal_driver::config ALIAS stm32h7xx_hal_driver_config)

target_include_directories(stm32h7xx_hal_driver_config INTERFACE
        .
)