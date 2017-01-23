set( APP_NAME demo ) 

project( ${APP_NAME} )

# Create list with sources.
set( SRC_PATH ${CMAKE_CURRENT_SOURCE_DIR}/src )

file( GLOB_RECURSE SOURCES ${SRC_PATH}/*.c )
file( GLOB_RECURSE HEADERS ${SRC_PATH}/*.h )

# Add include directory.
include_directories( ${SRC_PATH}
                     ${PROJECT_GENERATED}
                     ${PROJECT_ROOT}/common/include
                     ${PROJECT_ROOT}/app/libgcc/src
                     ${PROJECT_ROOT}/app/libc/src
                     ${PROJECT_ROOT}/app/libsys/src )

# Set build flags.
set( CMAKE_C_FLAGS "-O2 -g" )

# Set path to libraries search.
link_directories( ${PROJECT_OUT}/app/syslib )

# Build executable.
add_executable( ${APP_NAME} ${SOURCES} )
target_link_libraries( ${APP_NAME} libsys.a )
