cmake_minimum_required( VERSION 2.6 )

set( PROJECT_ROOT      ${CMAKE_CURRENT_SOURCE_DIR} )
set( PROJECT_OUT       ${CMAKE_CURRENT_BINARY_DIR} )
set( PROJECT_INSTALL   ${CMAKE_CURRENT_BINARY_DIR}/export )
set( PROJECT_GENERATED ${CMAKE_CURRENT_SOURCE_DIR}/common/generated )

add_subdirectory( app/libc )
add_subdirectory( app/gcclib )

################################################################################
# CONFIGURE
################################################################################

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
    set( CFG_ASSERTION "0" )
endif()

# -DCTYPE_1BYTE=<C-type name>
# -DCTYPE_2BYTE=<C-type name>
# -DCTYPE_4BYTE=<C-type name>
# -DCTYPE_8BYTE=<C-type name>
#
# Alias indicated C type with bitness 'typedef' types.
#
# Default:
#
# -DCTYPE_1BYTE=char
# -DCTYPE_2BYTE=short
# -DCTYPE_4BYTE=int
# -DCTYPE_8BYTE=long long
#
if( NOT DEFINED CTYPE_1BYTE )
    set( CTYPE_1BYTE "char" )
endif()

if( NOT DEFINED CTYPE_2BYTE )
    set( CTYPE_2BYTE "short" )
endif()

if( NOT DEFINED CTYPE_4BYTE )
    set( CTYPE_4BYTE "int" )
endif()

if( NOT DEFINED CTYPE_8BYTE )
    set( CTYPE_8BYTE "long long" )
endif()

configure_file( ${CMAKE_CURRENT_SOURCE_DIR}/config/configure_in/config.h.in ${PROJECT_GENERATED}/config.h @ONLY)
configure_file( ${CMAKE_CURRENT_SOURCE_DIR}/config/configure_in/typedef.h.in ${PROJECT_GENERATED}/typedef.h @ONLY)

# Install common headers.
file( GLOB_RECURSE COMMON_HEADERS ${PROJECT_ROOT}/common/*.h )

install( FILES ${COMMON_HEADERS} DESTINATION ${PROJECT_INSTALL} )
