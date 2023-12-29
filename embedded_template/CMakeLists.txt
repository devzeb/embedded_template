# business logic and device specific code

add_executable(embedded_template
        main.cpp
        gettimeofday.cpp
        gettimeofday.h
)

target_link_libraries(embedded_template PRIVATE
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
