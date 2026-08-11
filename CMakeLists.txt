cmake_minimum_required(VERSION 3.5)

project(taskqueue VERSION 1.0.0 LANGUAGES CXX)

find_package(Threads REQUIRED)

add_executable(taskqueue main.cpp workers.cpp)
add_executable(test_priority test_priority.cpp)
add_executable(test_stress test_stress.cpp)
add_executable(test_perf test_perf.cpp)

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