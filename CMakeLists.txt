cmake_minimum_required(VERSION 3.10.1)

project(
  GPUTerrain
  VERSION 0.0.0
)

set(SOURCES
  src/GPUTerrain.cpp
)

set(INCLUDES
  src/Fwd.h
  src/GPUTerrain.h
)

add_library(${PROJECT_NAME} ${SOURCES} ${INCLUDES})

target_include_directories(${PROJECT_NAME}
  PUBLIC src
)

option(${PROJECT_NAME}_BUILD_TESTS "toggle building of unit tests")
if(${PROJECT_NAME}_BUILD_TESTS)
  enable_testing()
  add_subdirectory(tests)
  add_test(NAME baseTest COMMAND tests)
endif()
