# cppevent

A header-only, basic on/emit event pattern using only C++11, including rudimentary timed events. Usage is inspired by NodeJS.

 Code tested with GCC 5.2.0 and CMake 3.3.2.

## Build it!

Simply put the `include` directory in your compiler search path and include `Eventer.hpp`. I have provided a cmake script to build my ```example.cpp```. simply follow these instructions:

1. ```mkdir cmko && cd cmko```
2. ```cmake -G "Unix Makefiles" ..```
2. ```make```