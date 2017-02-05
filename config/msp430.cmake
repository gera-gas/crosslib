include( CMakeForceCompiler )

set( CMAKE_SYSTEM_NAME "Generic" )
set( CMAKE_SYSTEM_VERSION 1 )
set( CMAKE_SYSTEM_PROCESSOR arm )

# Toolchain path settings.
if( WIN32 )
    set( TOOLCHAIN_DIR c:/SysGCC/msp430 )
else()
    set( TOOLCHAIN_DIR opt/msp430-toolchain )
endif()

set( TOOLCHAIN_DIR_BIN  ${TOOLCHAIN_DIR}/bin )
set( TOOLCHAIN_DIR_MSP  ${TOOLCHAIN_DIR}/msp430 )
set( TOOLCHAIN_DIR_INC  ${TOOLCHAIN_DIR_MSP}/include )
set( TOOLCHAIN_DIR_LIB  ${TOOLCHAIN_DIR_MSP}/lib )
set( TOOLCHAIN_DIR_LD   ${TOOLCHAIN_DIR_LIB}/ldscripts )
set( TOOLCHAIN_DIR_LDM  ${TOOLCHAIN_DIR_LD}/msp430f5529 )

# Toolchain compiler definitions.
set( GCC_PREF msp430- )

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

# Set default linker script.
set( LDSCRIPT_DEFAULT "-T${TOOLCHAIN_DIR_LD}/msp430.x" CACHE INTERNAL "")

# Set general options.
#set( CMAKE_C_FLAGS "-mmcu=msp430f5529 -Wall -gdwarf-2" CACHE INTERNAL "c compiler flags")
set( CMAKE_C_FLAGS "-mmcu=msp430f5529 -Wall" CACHE INTERNAL "c compiler flags")
set( CMAKE_EXE_LINKER_FLAGS "-mmcu=msp430f5529 -L${TOOLCHAIN_DIR_LD} -L${TOOLCHAIN_DIR_LDM} -L${TOOLCHAIN_DIR_LIB}" CACHE INTERNAL "exe link flags")
