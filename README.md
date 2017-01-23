## crosslib
Software project with cross compile library for embedded system.

## Tools
* CMake version 2.8.7+
* GNU Make

## Build
Build under Linux:

    $ mkdir build
    $ cd build
    $ cmake -Wno-dev -G "Eclipse CDT4 - Unix Makefiles" -DCMAKE_TOOLCHAIN_FILE=../config/toolchain.cmake ..
    $ cmake --build .

Build under Windows:

    > md build
    > cd build
    > cmake -Wno-dev -G "Eclipse CDT4 - Unix Makefiles" -DCMAKE_TOOLCHAIN_FILE=../config/toolchain.cmake ..
    > cmake --build .
