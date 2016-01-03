# Tested on G++ 5.2.0
cmake_minimum_required(VERSION 3.2)
project(cppevent)
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
    "${CMAKE_SOURCE_DIR}/submodules/readerwriterqueue"
    "${CMAKE_BINARY_DIR}/generated"
)

add_library(cppevent SHARED
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Eventer.cpp
)

target_link_libraries(cppevent
    -lpthread
)