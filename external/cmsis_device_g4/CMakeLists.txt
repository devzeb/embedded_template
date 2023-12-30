add_library(cmsis_device_g4 INTERFACE)
add_library(embedded_template::cmsis_device::g4 ALIAS cmsis_device_g4)

target_include_directories(cmsis_device_g4 INTERFACE
        cmsis_device_g4/Include/
)
target_link_libraries(cmsis_device_g4 INTERFACE
        embedded_template::cmsis_core
        embedded_template::cmsis_device_defines
)

