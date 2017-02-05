include( CMakeForceCompiler )

set( CMAKE_SYSTEM_NAME "Generic" )
set( CMAKE_SYSTEM_VERSION 1 )
set( CMAKE_SYSTEM_PROCESSOR powerpc-eabi )

# Toolchain compiler definitions.
set( GCC_PREF powerpc-eabi- )

if( WIN32 )
    CMAKE_FORCE_C_COMPILER(   "${GCC_PREF}gcc.exe" GNU )
    CMAKE_FORCE_CXX_COMPILER( "${GCC_PREF}g++.exe" GNU )
else()
    CMAKE_FORCE_C_COMPILER(   "${GCC_PREF}gcc" GNU )
    CMAKE_FORCE_CXX_COMPILER( "${GCC_PREF}g++" GNU )
endif()
