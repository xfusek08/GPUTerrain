
cmake_minimum_required(VERSION 3.12.4)

add_executable(gp_tests
    TestsMain.cpp
    catch.hpp
    testSuites/testSurface.cpp
    testSuites/testSurfaceModifier.cpp
)

target_include_directories(gp_tests
  PRIVATE ${CMAKE_CURRENT_LIST_DIR}
)

target_link_libraries(gp_tests GeoPlanetLib)
