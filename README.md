# cppevent

Basic on/emit event pattern using only C++11. Includes rudimentary timed events.

## Wha?
This is a small library using lambdas and threads for easy callback events. Please see src/example.cpp.

The CMakeLists here will allow you to build a shared lib from the code, but I find it easier to just include the source via git submodule.

## Build it!

I use CMake to generate Makefiles. Code tested with GCC 5.2.0 and CMake 3.3.2.

1. ```cmake -G "Unix Makefiles" .```
2. ```make```
3. (optional) ```./buildexample.sh```