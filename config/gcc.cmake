# Toolchain compiler definitions.
if( WIN32 )
    set( CMAKE_C_COMPILER   "gcc.exe" )
    set( CMAKE_CXX_COMPILER "g++.exe" )
else()
    set( CMAKE_C_COMPILER   "gcc" )
    set( CMAKE_CXX_COMPILER "g++" )
endif()
