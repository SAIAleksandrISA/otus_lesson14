cmake_minimum_required(VERSION 3.5)

project(taskqueue VERSION 1.0.0 LANGUAGES CXX)

enable_testing()

find_package(Threads REQUIRED)

include_directories("${CMAKE_CURRENT_SOURCE_DIR}/include")

add_executable(taskqueue src/main.cpp src/workers.cpp)
add_executable(test_priority tests/test_priority.cpp)
add_executable(test_stress tests/test_stress.cpp)
add_executable(test_perf tests/test_perf.cpp)

add_test(NAME PriorityTest COMMAND test_priority)
add_test(NAME StressTest   COMMAND test_stress)
add_test(NAME PerfTest     COMMAND test_perf)

target_link_libraries(taskqueue PRIVATE Threads::Threads)

set_target_properties(taskqueue PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS OFF
)

if (MSVC)
    target_compile_options(taskqueue PRIVATE /W4)
else ()
    target_compile_options(taskqueue PRIVATE -Wall -Wextra -pedantic -Werror)
endif()

configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/version.h.in" 
    "${CMAKE_BINARY_DIR}/version.h"          
)

target_include_directories(taskqueue PRIVATE "${CMAKE_BINARY_DIR}")