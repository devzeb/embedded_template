cmake_minimum_required(VERSION 3.26)

# "toolchain" related options
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR arm)

# make cmake test by compiling a static library instead of an executable
# this is required so the cmake internal test if the compiler works does not fail when using a cross-compiler
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

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

# compiler specific options (e.g. CMAKE_TRY_COMPILE_TARGET_TYPE)
# should be set before the project command
project(embedded_template
        CXX
        C
        ASM # required, because the startup file is written in assembly (./embedded_template/device_stm32h723/startup_stm32h723zgtx.s)
)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(external/cmsis)

if (EMBEDDED_TEMPLATE_DEVICE STREQUAL STM32H723xx)
    add_subdirectory(embedded_template/device_stm32h723)

    add_subdirectory(external/cmsis_device_h7)

    # target cmsis_device_h7 requires, that "a device is defined" using a preprocessor macro (= cmake compile definition)
    # this is, because the file external/cmsis_device_h7/cmsis_device_h7/Include/stm32h7xx.h prints an error message when
    # no device macro is defined
    #
    # this requirement is expressed in cmake by the fact that the cmake target cmsis_device_h7 from
    # ./external/cmsis_device_h7 links against embedded_template::cmsis_device_defines
    # this means we need to supply the target embedded_template::cmsis_device_defines, that includes the compile definition for the specific device used
    add_library(cmsis_device_defines INTERFACE)
    add_library(embedded_template::cmsis_device_defines ALIAS cmsis_device_defines)
    target_compile_definitions(cmsis_device_defines INTERFACE
            STM32H723xx
    )
else ()
    message(FATAL_ERROR "Unsupported device: ${EMBEDDED_TEMPLATE_DEVICE}")
endif ()

# all "project" specific files are located in the embedded_template subdirectory,
# all other subdirectories are dependencies
add_subdirectory(embedded_template)