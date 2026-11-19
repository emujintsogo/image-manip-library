cmake_minimum_required(VERSION 3.20)

project(image-manip LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Build the image library
add_library(image-manip
    src/image.cpp
)

target_include_directories(image-manip PUBLIC include)

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
    PRIVATE image-manip GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(test_image)