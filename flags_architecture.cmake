add_library(flags_mcu INTERFACE)

set(EMBEDDED_TEMPLATE_ARCH_FLAGS
        --specs=nano.specs
        -mthumb
)

target_compile_options(flags_mcu INTERFACE ${EMBEDDED_TEMPLATE_ARCH_FLAGS})
target_link_options(flags_mcu INTERFACE ${EMBEDDED_TEMPLATE_ARCH_FLAGS})

# make all following targets use the architecture specific compiler and linker flags
link_libraries(flags_mcu)

if (EMBEDDED_TEMPLATE_DEVICE STREQUAL STM32G474xx)
    add_library(flags_cpu INTERFACE)

    set(EMBEDDED_TEMPLATE_ARCH_FLAGS_CPU
            -mcpu=cortex-m4
            -mfloat-abi=hard
    )

    target_compile_options(flags_cpu INTERFACE ${EMBEDDED_TEMPLATE_ARCH_FLAGS_CPU})
    target_link_options(flags_cpu INTERFACE ${EMBEDDED_TEMPLATE_ARCH_FLAGS_CPU})

    # make all following targets use the architecture specific compiler and linker flags
    link_libraries(flags_cpu)
endif ()