# set EMBEDDED_TEMPLATE_DEVICE in cache
# can be overwritten by user (e.g. in cmake-gui or by editing CMakeCache.txt)
set(EMBEDDED_TEMPLATE_DEVICE STM32H723xx CACHE STRING "Device used for embedded_template")

if (EMBEDDED_TEMPLATE_DEVICE STREQUAL STM32H723xx)
    add_library(flags_mcu INTERFACE)

    set(EMBEDDED_TEMPLATE_ARCH_FLAGS
            --specs=nano.specs
            --specs=nosys.specs
            -mthumb
            -mcpu=cortex-m7
            -mfloat-abi=hard
    )

    target_compile_options(flags_mcu INTERFACE ${EMBEDDED_TEMPLATE_ARCH_FLAGS})
    target_link_options(flags_mcu INTERFACE ${EMBEDDED_TEMPLATE_ARCH_FLAGS})

    # make all following targets use the architecture specific compiler and linker flags
    link_libraries(flags_mcu)
else ()
    message(FATAL_ERROR "Unsupported device: ${EMBEDDED_TEMPLATE_DEVICE}")
endif ()
