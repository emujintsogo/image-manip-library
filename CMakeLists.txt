cmake_minimum_required(VERSION 3.20)

project(image-manip LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

option(IMAGE_MANIP_WARNINGS_AS_ERRORS "Treat warnings as errors" OFF)

add_library(image-manip-warnings INTERFACE)
target_compile_options(image-manip-warnings INTERFACE
    $<$<CXX_COMPILER_ID:MSVC>:/W4>
    $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wextra -Wpedantic -Wconversion -Wsign-conversion>
)
if(IMAGE_MANIP_WARNINGS_AS_ERRORS)
    target_compile_options(image-manip-warnings INTERFACE
        $<$<CXX_COMPILER_ID:MSVC>:/WX>
        $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Werror>
    )
endif()

# Build the image library
add_library(image-manip
    src/image.cpp
)

target_include_directories(image-manip PUBLIC include)
target_link_libraries(image-manip PRIVATE image-manip-warnings)

# Download and configure GoogleTest
include(FetchContent)

FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.17.0.zip
)

FetchContent_MakeAvailable(googletest)

# Build the tests
enable_testing()

add_executable(test_image
    tests/test_image.cpp
)

target_link_libraries(test_image
    PRIVATE image-manip image-manip-warnings GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(test_image)