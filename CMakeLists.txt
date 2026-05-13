cmake_minimum_required(VERSION 3.15)

project(
    mural
    VERSION 0.0.1
    DESCRIPTION "A lightweight 2D raster graphics and canvas library written in C."
    LANGUAGES C
    )

    
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

option(MRL_BUILD_EXAMPLES "Build examples" ON)
option(MRL_BUILD_TESTS "Build tests" ON)
option(MRL_ENABLE_PNG "Enable PNG support" ON)

if(MRL_ENABLE_PNG)
    find_package(PNG REQUIRED)
endif()

file(GLOB MRL_DRAWABLE_SOURCES
    src/drawables/*.c
)

set(MRL_SOURCES
    src/canvas.c
    src/drawable.c
    src/color.c
    src/image.c
    src/image_ppm.c
    ${MRL_DRAWABLE_SOURCES}
)

if(MRL_ENABLE_PNG)
    list(APPEND MRL_SOURCES
        src/image_png.c
    )
endif()

add_library(mural ${MRL_SOURCES})

configure_file(
    include/mrl/config.h.in
    ${CMAKE_CURRENT_BINARY_DIR}/generated/mrl/config.h
)

target_include_directories(mural
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/generated>
        $<INSTALL_INTERFACE:include>

    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_compile_options(mural PRIVATE
    -Wall
    -Wextra
    -Wpedantic
    -fvisibility=hidden
)

if(MRL_ENABLE_PNG)
    target_link_libraries(mural
        PRIVATE PNG::PNG)
endif()

if(MRL_BUILD_EXAMPLES)
    add_executable(hello
        examples/hello.c
    )

    target_link_libraries(hello PRIVATE mural)
endif()

if(MRL_BUILD_TESTS)
    enable_testing()

    add_executable(test_basic
        tests/test_basic.c
    )

    target_link_libraries(test_basic PRIVATE mural)

    add_test(NAME basic COMMAND test_basic)
endif()

install(TARGETS mural)
install(DIRECTORY include/ DESTINATION include)