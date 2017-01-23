set( APP_NAME c ) 

project( ${APP_NAME} )

# Create list with sources.
set( SRC_PATH ${CMAKE_CURRENT_SOURCE_DIR}/src )

file( GLOB_RECURSE SOURCES ${SRC_PATH}/*.c )
file( GLOB_RECURSE HEADERS ${SRC_PATH}/*.h )

# Add include directory.
include_directories( ${SRC_PATH}
                     ${PROJECT_GENERATED}
                     ${PROJECT_ROOT}/common/include )

# Set build flags.
set( CMAKE_C_FLAGS "-O2 -g -fno-builtin-strlen -fno-builtin-strchr -fno-builtin-strrchr -fno-builtin-pow -fno-builtin-free -fno-builtin-malloc -fno-builtin-calloc -fno-builtin-memset -fno-builtin-memcpy -fno-builtin-memmove -fno-builtin-memcmp -fno-builtin-pow -fno-builtin-labs" )

# Build static library.
add_library( ${APP_NAME} STATIC ${SOURCES} )

# Would be done with use: 'make install'.
install( TARGETS ${APP_NAME} DESTINATION ${PROJECT_INSTALL}/${CMAKE_STATIC_LIBRARY_PREFIX}${APP_NAME} )
install( FILES   ${HEADERS}  DESTINATION ${PROJECT_INSTALL}/${CMAKE_STATIC_LIBRARY_PREFIX}${APP_NAME}/include )
