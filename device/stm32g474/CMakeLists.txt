add_library(device_stm32g474_shared_system INTERFACE)
add_library(embedded_template::device ALIAS device_stm32g474_shared_system)

set(LINKER_SCRIPT ${CMAKE_CURRENT_SOURCE_DIR}/STM32G474RETX_FLASH.ld) # absolute path is required

# relink the target when the linker script is changed
set_property(TARGET device_stm32g474_shared_system PROPERTY INTERFACE_LINK_DEPENDS ${LINKER_SCRIPT})

# make all targets that link to this target use the linker script
target_link_options(device_stm32g474_shared_system INTERFACE -Wl,-T${LINKER_SCRIPT})

target_sources(device_stm32g474_shared_system INTERFACE
        system_stm32g4xx.c
        startup_stm32g474retx.s
)

target_link_libraries(device_stm32g474_shared_system INTERFACE
        embedded_template::cmsis_device::g4
)