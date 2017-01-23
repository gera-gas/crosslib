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
set( TOOLCHAIN_DIR_ARM  ${TOOLCHAIN_DIR}/arm-eabi )
set( TOOLCHAIN_DIR_INC  ${TOOLCHAIN_DIR_ARM}/include )
set( TOOLCHAIN_DIR_LIB  ${TOOLCHAIN_DIR_ARM}/lib )
set( TOOLCHAIN_DIR_LD   ${TOOLCHAIN_DIR_LIB}/ldscripts )

# Toolchain compiler definitions.
set( GCC_PREF arm-eabi- )

if( WIN32 )
    CMAKE_FORCE_C_COMPILER(   "${GCC_PREF}gcc.exe" GNU )
    CMAKE_FORCE_CXX_COMPILER( "${GCC_PREF}g++.exe" GNU )
else()
    CMAKE_FORCE_C_COMPILER(   "${GCC_PREF}gcc" GNU )
    CMAKE_FORCE_CXX_COMPILER( "${GCC_PREF}g++" GNU )
endif()
