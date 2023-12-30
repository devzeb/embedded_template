add_subdirectory(cmsis)

if (EMBEDDED_TEMPLATE_DEVICE STREQUAL STM32G474xx)
    add_subdirectory(cmsis_device_g4)
    add_subdirectory(stm32g4xx_hal_driver)

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
            STM32G474xx
    )
else ()
    message(FATAL_ERROR "Unsupported device: ${EMBEDDED_TEMPLATE_DEVICE}")
endif ()