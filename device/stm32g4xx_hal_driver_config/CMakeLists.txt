add_library(stm32g4xx_hal_driver_config INTERFACE)
add_library(embedded_template::stm32g4xx_hal_driver::config ALIAS stm32g4xx_hal_driver_config)

target_include_directories(stm32g4xx_hal_driver_config INTERFACE
        .
)