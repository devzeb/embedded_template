cmake_minimum_required(VERSION 3.26)

# "toolchain" related options
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR arm)

# make cmake test by compiling a static library instead of an executable
# this is required so the cmake internal test if the compiler works does not fail when using a cross-compiler
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

include(flags_architecture.cmake)

# compiler specific options (e.g. CMAKE_TRY_COMPILE_TARGET_TYPE)
# should be set before the project command
project(embedded_template
        CXX
        C
        ASM # required, because the startup file is written in assembly (./embedded_template/device_stm32h723/startup_stm32h723zgtx.s)
)

set(CMAKE_CXX_STANDARD 20)

include(flags_compiler_linker.cmake)

add_subdirectory(external)
add_subdirectory(device)

# all "project" specific files are located in the embedded_template subdirectory,
# all other subdirectories are dependencies
add_subdirectory(embedded_template)