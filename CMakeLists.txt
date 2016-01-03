# Tested on G++ 5.2.0
cmake_minimum_required(VERSION 2.8)
project(cppevent-example)
#find_package(PkgConfig)

set(CMAKE_VERBOSE_MAKEFILE false)

set(warnings "-Wall -Wextra")

if (NOT CONFIGURED_ONCE)
    set(CMAKE_CXX_FLAGS "-std=c++11 ${warnings}"
        CACHE STRING "Flags used by the compiler during all build types." FORCE)
    set(CMAKE_C_FLAGS   "${warnings}"
        CACHE STRING "Flags used by the compiler during all build types." FORCE)
endif()

### BUILD TARGETS ###

include_directories(AFTER
    "${CMAKE_SOURCE_DIR}/include"
)

add_executable(cppevent-example
    ${CMAKE_CURRENT_SOURCE_DIR}/src/example.cpp
)

target_link_libraries(cppevent-example
    -lpthread
)