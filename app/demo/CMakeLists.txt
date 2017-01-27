set( APP_NAME demo ) 

project( ${APP_NAME} )

# Create list with sources.
set( SRC_PATH ${CMAKE_CURRENT_SOURCE_DIR}/src )

# Add include directory.
include_directories( ${SRC_PATH}
                     ${PROJECT_GENERATED}
                     ${PROJECT_ROOT}/common/include
                     ${PROJECT_ROOT}/app/gcclib/src
                     ${PROJECT_ROOT}/app/libc/src
                     ${PROJECT_ROOT}/app/syslib/src )

# Set build flags.
set( CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O2 -g" )

# Set path to libraries search.
link_directories( ${PROJECT_OUT}/app/syslib )

# Build executable.
add_executable( ${APP_NAME}_pt ${SRC_PATH}/demo_pt.c )
target_link_libraries( ${APP_NAME}_pt libsys.a )

add_executable( ${APP_NAME}_fixlock ${SRC_PATH}/demo_fixlock.c )
target_link_libraries( ${APP_NAME}_fixlock libsys.a )
