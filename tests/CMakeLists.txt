cmake_minimum_required(VERSION 3.10.1)

add_executable(tests tests.cpp catch.hpp)

target_include_directories(tests
  PRIVATE ${CMAKE_CURRENT_LIST_DIR}
)

target_link_libraries(tests TerrainLib)
