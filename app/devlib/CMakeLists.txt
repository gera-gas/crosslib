set( APP_NAME dev ) 

project( ${APP_NAME} )

# Create list with sources.
set( SRC_PATH ${CMAKE_CURRENT_SOURCE_DIR}/src )

file( GLOB_RECURSE SOURCES ${SRC_PATH}/*.c )
file( GLOB_RECURSE HEADERS ${SRC_PATH}/*.h )

# Add include directory.
include_directories( ${SRC_PATH}
                     ${PROJECT_GENERATED}
                     ${PROJECT_ROOT}/common/include
                     ${PROJECT_ROOT}/app/libc/src
                     ${PROJECT_ROOT}/app/gcclib/src
                     ${PROJECT_ROOT}/app/syslib/src )

# Set build flags.
set( CMAKE_C_FLAGS "-O2 -g" )

# Build static library.
add_library( ${APP_NAME} STATIC ${SOURCES} )

# Would be done with use: 'make install'.
install( TARGETS ${APP_NAME} DESTINATION ${PROJECT_INSTALL}/${CMAKE_STATIC_LIBRARY_PREFIX}${APP_NAME} )
install( FILES   ${HEADERS}  DESTINATION ${PROJECT_INSTALL}/${CMAKE_STATIC_LIBRARY_PREFIX}${APP_NAME}/include )

# Install PowerPC library files.
file( GLOB_RECURSE CPU_PPC_SRC ${SRC_PATH}/cpu/powerpc/405/*.S )

install( FILES ${CPU_PPC_SRC} DESTINATION ${PROJECT_INSTALL}/${CMAKE_STATIC_LIBRARY_PREFIX}${APP_NAME}/src/ppc405 )
