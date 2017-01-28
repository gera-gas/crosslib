include( CMakeForceCompiler )

set( CMAKE_SYSTEM_NAME "Generic" )
set( CMAKE_SYSTEM_VERSION 1 )
set( CMAKE_SYSTEM_PROCESSOR arm )

# Toolchain path settings.
if( WIN32 )
    set( TOOLCHAIN_DIR c:/SysGCC/arm-eabi )
else()
    set( TOOLCHAIN_DIR opt/arm-toolchain )
endif()

set( TOOLCHAIN_DIR_BIN  ${TOOLCHAIN_DIR}/bin )
set( TOOLCHAIN_DIR_CPU  ${TOOLCHAIN_DIR}/arm-eabi )
set( TOOLCHAIN_DIR_INC  ${TOOLCHAIN_DIR_CPU}/include )
set( TOOLCHAIN_DIR_LIB  ${TOOLCHAIN_DIR_CPU}/lib )
set( TOOLCHAIN_DIR_LD   ${TOOLCHAIN_DIR_LIB}/ldscripts )

# Toolchain compiler definitions.
set( GCC_PREF arm-eabi- )

if( WIN32 )
    CMAKE_FORCE_C_COMPILER(   "${GCC_PREF}gcc.exe" GNU )
    CMAKE_FORCE_CXX_COMPILER( "${GCC_PREF}g++.exe" GNU )

    set( CMAKE_OBJCOPY ${GCC_PREF}objcopy.exe CACHE INTERNAL "")
    set( CMAKE_OBJDUMP ${GCC_PREF}objdump.exe CACHE INTERNAL "")
    set( CMAKE_SIZE    ${GCC_PREF}size.exe    CACHE INTERNAL "")
else()
    CMAKE_FORCE_C_COMPILER(   "${GCC_PREF}gcc" GNU )
    CMAKE_FORCE_CXX_COMPILER( "${GCC_PREF}g++" GNU )

    set( CMAKE_OBJCOPY ${GCC_PREF}objcopy CACHE INTERNAL "")
    set( CMAKE_OBJDUMP ${GCC_PREF}objdump CACHE INTERNAL "")
    set( CMAKE_SIZE    ${GCC_PREF}size    CACHE INTERNAL "")
endif()

# Set build flags.
set( CMAKE_C_FLAGS "-mthumb -mcpu=cortex-m3 -Wall -mlittle-endian" CACHE INTERNAL "c compiler flags")
set( CMAKE_CXX_FLAGS "-mthumb -mcpu=cortex-m3 -Wall" CACHE INTERNAL "cxx compiler flags")
set( CMAKE_EXE_LINKER_FLAGS "-nostartfiles -Wl,-Map -Wl,main.map -mthumb -mcpu=cortex-m3 -L${TOOLCHAIN_DIR_LIB}" CACHE INTERNAL "exe link flags")
