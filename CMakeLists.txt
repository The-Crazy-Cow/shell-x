# SPDX-License-Identifier: GPL-2.0

cmake_minimum_required(VERSION 3.10)
project(shell-x LANGUAGES C)

file(GLOB_RECURSE SOURCE_FILES
    "${CMAKE_SOURCE_DIR}/src/core/*.c"
    "${CMAKE_SOURCE_DIR}/src/main.c"
    "${CMAKE_SOURCE_DIR}/include/*.h"
    "${CMAKE_SOURCE_DIR}/utils/*.h"
    "${CMAKE_SOURCE_DIR}/utils/*.c"
)

#------| formating code text with clang-format
find_program(CLANG_FORMAT_BIN NAMES clang-format clang-format-16 clang-format-15)

if(CLANG_FORMAT_BIN)
    add_custom_target(format
        COMMAND ${CLANG_FORMAT_BIN} -i -style=file ${SOURCE_FILES}
        COMMENT "Formating code with clang-format..."
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    )
else()
    message(WARNING "clang-format package not found. target 'format' not avalaible.")
endif()

#------| documentation with Doxygen
find_package(Doxygen)

if(DOXYGEN_FOUND)
    add_custom_target(doc
        COMMAND ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        COMMENT "spawn documentation with Doxygen..."
        VERBATIM
    )
endif()

add_subdirectory(src)