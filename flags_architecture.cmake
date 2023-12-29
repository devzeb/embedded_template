add_library(flags_mcu INTERFACE)

set(EMBEDDED_TEMPLATE_ARCH_FLAGS
        --specs=nano.specs
        -mthumb
)

target_compile_options(flags_mcu INTERFACE ${EMBEDDED_TEMPLATE_ARCH_FLAGS})
target_link_options(flags_mcu INTERFACE ${EMBEDDED_TEMPLATE_ARCH_FLAGS})

# make all following targets use the architecture specific compiler and linker flags
link_libraries(flags_mcu)

if (EMBEDDED_TEMPLATE_DEVICE STREQUAL STM32H723xx)
    add_library(flags_cpu INTERFACE)

    set(EMBEDDED_TEMPLATE_ARCH_FLAGS_DEVICE
            -mcpu=cortex-m7
            -mfloat-abi=hard
    )

    target_compile_options(flags_cpu INTERFACE ${EMBEDDED_TEMPLATE_ARCH_FLAGS_DEVICE})
    target_link_options(flags_cpu INTERFACE ${EMBEDDED_TEMPLATE_ARCH_FLAGS_DEVICE})

    # make all following targets use the architecture specific compiler and linker flags
    link_libraries(flags_cpu)
else ()
    message(FATAL_ERROR "Unsupported device: ${EMBEDDED_TEMPLATE_DEVICE}")
endif ()
