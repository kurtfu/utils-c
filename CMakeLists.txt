cmake_minimum_required(VERSION 3.17.0)
project(utils LANGUAGES C CXX)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

enable_testing()
add_subdirectory(doctest)

if (MSVC)
    add_compile_options(/Wall)
else()
    add_compile_options(-Wall -Wextra -pedantic)
endif()

include_directories(
    cbuf
)

add_executable(utils-test
    cbuf/cbuf.c
    test/cbuf.cpp
)

target_link_libraries(utils-test doctest::doctest)

include(doctest/scripts/cmake/doctest.cmake)
doctest_discover_tests(utils-test)
