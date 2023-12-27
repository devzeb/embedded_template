add_library(cmsis_device_h7 INTERFACE)
add_library(embedded_template::cmsis_device::h7 ALIAS cmsis_device_h7)

target_include_directories(cmsis_device_h7 INTERFACE
        cmsis_device_h7/Include/
)
target_link_libraries(cmsis_device_h7 INTERFACE
        embedded_template::cmsis_core
        embedded_template::cmsis_device_defines
)

