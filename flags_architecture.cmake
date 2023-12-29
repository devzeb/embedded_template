add_library(flags_mcu INTERFACE)

set(EMBEDDED_TEMPLATE_ARCH_FLAGS
        --specs=nano.specs
        -mthumb
)

target_compile_options(flags_mcu INTERFACE ${EMBEDDED_TEMPLATE_ARCH_FLAGS})
target_link_options(flags_mcu INTERFACE ${EMBEDDED_TEMPLATE_ARCH_FLAGS})

# make all following targets use the architecture specific compiler and linker flags
link_libraries(flags_mcu)
