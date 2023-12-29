# business logic and device specific code

add_executable(embedded_template
        main.cpp
)

target_link_libraries(embedded_template PRIVATE
        embedded_template::device
        embedded_template::flags_compiler_linker_config # use the flags defined below
)


add_library(flags_compiler_linker_config INTERFACE)
add_library(embedded_template::flags_compiler_linker_config ALIAS flags_compiler_linker_config)

set(GENERIC_FLAGS
        # the following two flags control that unused functions and data items can be removed by the linker using -Wl,--gc-sections
        # this does decrease the size of the binary
        -ffunction-sections # place each function in its own section in the output file
        -fdata-sections # place each data item in its own section in the output file
)

set(ASM_FLAGS
        -x;assembler-with-cpp
)

set(C_FLAGS
)

set(CPP_FLAGS
        -fno-rtti
        -fno-exceptions

        # the compiler places uninitialized global variables in the BSS section of the object file
        # you get a multiple-definition error if the same variable is accidentally defined in more than one compilation unit
        # https://gcc.gnu.org/onlinedocs/gcc/Code-Gen-Options.html
        -fno-common

        -fno-non-call-exceptions
        -fno-use-cxa-atexit
)

set(DEBUG_FLAGS
)

set(RELEASE_FLAGS
)


target_compile_options(flags_compiler_linker_config INTERFACE
        ${GENERIC_FLAGS}
        "$<$<COMPILE_LANGUAGE:ASM>:${ASM_FLAGS}>"
        "$<$<COMPILE_LANGUAGE:C>:${C_FLAGS}>"
        "$<$<COMPILE_LANGUAGE:CXX>:${CPP_FLAGS}>"
        "$<$<CONFIG:Debug>:${DEBUG_FLAGS}>"
        "$<$<CONFIG:Release>:${RELEASE_FLAGS}>"
)

target_link_options(flags_compiler_linker_config INTERFACE
        -Wl,--gc-sections # remove unused symbols (requires -ffunction-sections -fdata-sections )

        -Wl,--print-memory-usage # print memory usage
)

# check if CMAKE_CXX_COMPILER ends with "arm-none-eabi-g++"
# cmake_path(GET <path-var> FILENAME <out-var>)
cmake_path(GET CMAKE_CXX_COMPILER STEM CXX_COMPILER_NAME) # stem is the file name without extension

if (CXX_COMPILER_NAME STREQUAL "arm-none-eabi-g++")
    # replace the file name of PATH_TO_CXX_COMPILER  with "arm-none-eabi-objdump"
    cmake_path(REPLACE_FILENAME CMAKE_CXX_COMPILER arm-none-eabi-objdump OUTPUT_VARIABLE PATH_TO_OBJDUMP)
    # if host is windows
    if (CMAKE_HOST_WIN32)
        # append .exe
        cmake_path(APPEND_STRING PATH_TO_OBJDUMP ".exe")
    endif ()

    #check if file exists
    if (EXISTS ${PATH_TO_OBJDUMP})
        # add custom target to disassemble the binary
        add_custom_target(disassemble
                COMMAND ${PATH_TO_OBJDUMP} --disassemble --demangle --source $<TARGET_FILE:embedded_template> > ${CMAKE_BINARY_DIR}/embedded_template.disassembly
                DEPENDS embedded_template
        )

        add_custom_target(disassemble-all
                COMMAND ${PATH_TO_OBJDUMP} --disassemble-all --demangle --source $<TARGET_FILE:embedded_template> > ${CMAKE_BINARY_DIR}/embedded_template.disassembly-all
                DEPENDS embedded_template
        )
    else ()
        message(WARNING "Could not find arm-none-eabi-objdump. It is not next to ${CMAKE_CXX_COMPILER}. Unable to add a disassembly target.")
    endif ()

else ()
    message(WARNING "CMAKE_CXX_COMPILER is not arm-none-eabi-g++, will not add disassembly target, but will still compile")
endif ()
