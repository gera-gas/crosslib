set( APP_NAME sys ) 

project( ${APP_NAME} )

# Create list with sources.
set( SRC_PATH ${CMAKE_CURRENT_SOURCE_DIR}/src )

file( GLOB_RECURSE SOURCES ${SRC_PATH}/*.c ${SRC_PATH}/*.cpp )
file( GLOB_RECURSE HEADERS ${SRC_PATH}/*.h ${SRC_PATH}/*.hpp )

# Add include directory.
include_directories( ${SRC_PATH}
                     ${PROJECT_GENERATED}
                     ${PROJECT_ROOT}/common/include
                     ${PROJECT_ROOT}/app/libc/src )

# Set build flags.
set( CMAKE_C_FLAGS "${CMAKE_C_FLAGS}" )
set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}" )

# Build static library.
add_library( ${APP_NAME} STATIC ${SOURCES} )

# Would be done with use: 'make install'.
install( TARGETS ${APP_NAME} DESTINATION ${PROJECT_INSTALL}/${CMAKE_STATIC_LIBRARY_PREFIX}${APP_NAME} )
install( FILES   ${HEADERS}  DESTINATION ${PROJECT_INSTALL}/${CMAKE_STATIC_LIBRARY_PREFIX}${APP_NAME}/include )
