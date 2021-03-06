## crosslib
Software project with cross compile library for embedded system.
Library collections contain:
* devlib -- drivers for any devices and hardware modules.
* gcclib -- part of standard GCC compiler files.
* libc   -- some files standard C library.
* [syslib](app/syslib/) -- library for system creation. (Pseudo thread, simple and fast non-blocking lock-free mechanism, HAL, IO, etc).

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
* 0 -- kick all assert macros from source code (default).
* 1 -- add simple assert macros with halt only (recommended for raw system).
* 2 -- add assert macros with output to STDOUT by fprintf.

###### -Dint[bits]=[C-type name]
Set specific bitness types in `typedef.h`.
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

###### -DUSE_BUILTIN_LIBC
Enable using builtin LIBC functions from GCC compiler.
Else LIBC will be used from [app]/[libc].

###### -DUSE_REGEXP_LOCALE
Enable using compare in regular expression by locale mechanism.
If locale and USE_BUILTIN_LIBC is not set, compare using only C locale (ASCII).

###### -DCPUINIT_CXX
Including C++ global initialization/deinitializtion code into
CPU boot code of [devlib]/[cpu]/[...].

###### -DCXX_RTTI
If defined, build class with RTTI supports.

###### -DCFG_ERROR_DETAILS
Enable fatal error details store.
Error details: source code file, line, function name.

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
