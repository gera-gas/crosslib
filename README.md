## crosslib
Software project with cross compile library for embedded system.
Library collections contain:
* devlib -- drivers for any device and hardware modules.
* gcclib -- part of standard GCC compiler files.
* libc   -- some files standard C library.
* [syslib](app/syslib/) -- library for system creation. (Pseudo thread mechanisms. Simple and fast non locking lock-free mechanisms).

## Tools
* [CMake version 2.8.7+](https://cmake.org/download/)
* GNU Make

## Configure
List CMake definitions for config project.

###### -DBUILD_DEMO
Build demo executables. It can be used only for MinGW build.
Because in examples used a Windows mechanisms.

###### -DASSERT=[0,1,2]
Defined to control assert macros.
* 0 -- kick all assert macros from source code.
* 1 -- add simple assert macros with halt only (recommended for raw system).
* 2 -- add assert macros with output to STDOUT by fprintf.

###### -Dint[bits]=[C-type name]
Alias indicated C type with bitness 'typedef' types.
Default:
* -Dint8=int8_t
* -Duint8=uint8_t
* -Dint16=int16_t
* -Duint16=uint16_t
* -Dint32=int32_t
* -Duint32=uint32_t
* -Dint64=int64_t
* -Duint64=uint64_t

###### -DNOSTDINC_STDINT_H
Kick standard include header file - `stdint.h.`
Should be set in CMake top project by `add_definitions( -DNOSTDINC_STDINT_H )`

## Build
Library building is expected as part of your top CMake project.
Examples of standalone build you can find in `[tools]` directory.
Below shown example standalone build.

    $ mkdir build
    $ cd build
    $ cmake -Wno-dev -G "Unix Makefiles" -DCMAKE_TOOLCHAIN_FILE=../config/<toolchain>.cmake ..
    $ cmake --build .
    $ make install

After installing libraries and headers will be copied to `[build]/[export]`.

## Note
Library oriented on GCC compiler.
