cmake_minimum_required(VERSION 3.15)

project(
    kanvas
    VERSION 0.1.0
    DESCRIPTION "Tiny software rendering library"
    LANGUAGES C
    )

find_package(PNG REQUIRED)
    
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

option(KVS_BUILD_EXAMPLES "Build examples" ON)
option(KVS_BUILD_TESTS "Build tests" ON)

file(GLOB KVS_DRAWABLE_SOURCES
    src/drawables/*.c
)

add_library(kanvas
    src/canvas.c
    src/drawable.c
    src/color.c
    src/image.c
    src/image_ppm.c
    src/image_png.c
    ${KVS_DRAWABLE_SOURCES}
)

target_include_directories(kanvas
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>

    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_compile_options(kanvas PRIVATE
    -Wall
    -Wextra
    -Wpedantic
    -fvisibility=hidden
)

target_link_libraries(kanvas
    PRIVATE PNG::PNG)

if(KVS_BUILD_EXAMPLES)
    add_executable(hello
        examples/hello.c
    )

    target_link_libraries(hello PRIVATE kanvas)
endif()

if(KVS_BUILD_TESTS)
    enable_testing()

    add_executable(test_basic
        tests/test_basic.c
    )

    target_link_libraries(test_basic PRIVATE kanvas)

    add_test(NAME basic COMMAND test_basic)
endif()

install(TARGETS kanvas)
install(DIRECTORY include/ DESTINATION include)