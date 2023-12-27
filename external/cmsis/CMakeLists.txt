add_library(cmsis_core INTERFACE)

# add the includes of cmsis as system includes
target_include_directories(cmsis_core SYSTEM INTERFACE
        CMSIS_5/CMSIS/Core/Include/
)

target_compile_definitions(cmsis_core INTERFACE
        -D__PROGRAM_START
)

add_library(embedded_template::cmsis_core ALIAS cmsis_core)