cmake_minimum_required( VERSION 2.6 )

set( PROJECT_ROOT      ${CMAKE_CURRENT_SOURCE_DIR} )
set( PROJECT_OUT       ${CMAKE_CURRENT_BINARY_DIR} )
set( PROJECT_INSTALL   ${CMAKE_CURRENT_BINARY_DIR}/export )
set( PROJECT_GENERATED ${CMAKE_CURRENT_SOURCE_DIR}/common/generated )

################################################################################
# CONFIGURE
################################################################################

# -DBUILD_DEMO
# 
# Build demo executables.
#
if( DEFINED BUILD_DEMO )
    set( BUILD_DEMO "ENABLE" )
endif()

# -DASSERT=[0,1,2]
#
# Defined to control 'assert' macros.
#
# 0 - kick all 'assert' macros from source code.
# 1 - add simple 'assert' macros with halt only (recommended for raw system).
# 2 - add 'assert' macros with output to STDOUT by fprintf.
#
if( ${ASSERT} MATCHES "[012]" )
    set( CFG_ASSERTION ${ASSERT} )
else()
    set( CFG_ASSERTION "1" )
endif()

# -Dint8=<C-type name>
# -Duint8=<C-type name>
# -Dint16=<C-type name>
# -Duint16=<C-type name>
# -Dint32=<C-type name>
# -Duint32=<C-type name>
# -Dint64=<C-type name>
# -Duint64=<C-type name>
#
# Alias indicated C type with bitness 'typedef' types.
#
# Default:
#
# -Dint8=int8_t
# -Duint8=uint8_t
# -Dint16=int16_t
# -Duint16=uint16_t
# -Dint32=int32_t
# -Duint32=uint32_t
# -Dint64=int64_t
# -Duint64=uint64_t
#
if( NOT DEFINED int8 )
    set( int8 "int8_t" )
endif()
if( NOT DEFINED uint8 )
    set( uint8 "uint8_t" )
endif()

if( NOT DEFINED int16 )
    set( int16 "int16_t" )
endif()
if( NOT DEFINED uint16 )
    set( uint16 "uint16_t" )
endif()

if( NOT DEFINED int32 )
    set( int32 "int32_t" )
endif()
if( NOT DEFINED uint32 )
    set( uint32 "uint32_t" )
endif()

if( NOT DEFINED int64 )
    set( int64 "int64_t" )
endif()
if( NOT DEFINED uint64 )
    set( uint64 "uint64_t" )
endif()

# -DNOSTDINC_STDINT_H
# 
# Kick standard include header file - stdint.h.
#
if( DEFINED NOSTDINC_STDINT_H )
    set( NOSTDINC_STDINT_H "1" )
endif()

# -DUSE_BUILTIN_LIBC
# 
# Enable using builtin LIBC functions from GCC compiler.
# Else LIBC will be used from [app]/[libc].
#
if( DEFINED USE_BUILTIN_LIBC )
    set( USE_BUILTIN_LIBC "1" )
endif()

# -DUSE_REGEXP_LOCALE
#
# Enable using compare in regular expression by locale mechanism.
# If locale and USE_BUILTIN_LIBC is not set, compare using only C locale (ASCII).
#
if( DEFINED USE_REGEXP_LOCALE )
    set( USE_REGEXP_LOCALE "1" )
endif()

# -DCPUINIT_CXX
#
# Including C++ global initialization/deinitializtion code into
# CPU boot code of [devlib]/[cpu]/[...].
#
if( DEFINED CPUINIT_CXX )
    set( CPUINIT_CXX "1" )
endif()

# -DCXX_RTTI
#
# If defined, build class with RTTI supports.
#
if( DEFINED CXX_RTTI )
    set( CXX_RTTI "1" )
endif()

configure_file( ${CMAKE_CURRENT_SOURCE_DIR}/config/configure_in/config.h.in ${PROJECT_GENERATED}/config.h @ONLY)
configure_file( ${CMAKE_CURRENT_SOURCE_DIR}/config/configure_in/typedef.h.in ${PROJECT_GENERATED}/typedef.h @ONLY)

# add subprojects.
add_subdirectory( app/libc )
add_subdirectory( app/gcclib )
add_subdirectory( app/syslib )
add_subdirectory( app/devlib )

if( ${BUILD_DEMO} MATCHES "ENABLE" )
    add_subdirectory( app/demo )
endif()

# Install common headers.
file( GLOB_RECURSE COMMON_HEADERS ${PROJECT_ROOT}/common/*.h )

install( FILES ${COMMON_HEADERS} DESTINATION ${PROJECT_INSTALL} )
