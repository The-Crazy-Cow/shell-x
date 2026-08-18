# SPDX-License-Identifier: GPL-2.0

add_executable(${PROJECT_NAME} main.c)

target_compile_features(${PROJECT_NAME} PRIVATE
    c_std_11
)

target_compile_definitions(${PROJECT_NAME} PRIVATE
    $<$<CONFIG:Debug>:DEBUG>
)

target_include_directories(${PROJECT_NAME} PRIVATE
    ../include
)

target_compile_options(${PROJECT_NAME} PRIVATE
    -Wall
    -Wextra
    -Wpedantic
    -Wshadow
    -Werror
    -Wconversion
    -Wformat=2
)
