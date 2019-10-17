#
# Author: Petr Fusek
#

cmake_minimum_required(VERSION 3.10.1)

project(
  TerrainLib
  VERSION 0.0.0
)

# find GPUengine library
if(NOT TARGET GPUEngine)
    find_package(GPUEngine COMPONENTS REQUIRED
        geCore
        geGL
        geUtil
    )
endif()

if(NOT TARGET glm)
  find_package(glm REQUIRED)
endif()

SET(CMAKE_DEBUG_POSTFIX           "d"  CACHE STRING "add a postfix, usually d on windows")
SET(CMAKE_RELEASE_POSTFIX         ""   CACHE STRING "add a postfix, usually empty on windows")
SET(CMAKE_RELWITHDEBINFO_POSTFIX  "rd" CACHE STRING "add a postfix, usually empty on windows")
SET(CMAKE_MINSIZEREL_POSTFIX      "s"  CACHE STRING "add a postfix, usually empty on windows")

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_INCLUDE_CURRENT_DIR_IN_INTERFACE ON)

set(DEFAULT_RESOERCES_PATH "${CMAKE_CURRENT_LIST_DIR}/resources")
set(${APP_NAME}_RESOURCES  "${DEFAULT_RESOERCES_PATH}" CACHE PATH "Relative or absolute path to Application resources.")

set(SRC_TERRAINLIB
    src/${PROJECT_NAME}/SurfaceRegion.h             src/${PROJECT_NAME}/SurfaceRegion.cpp
    src/${PROJECT_NAME}/PlanetSurface.h             src/${PROJECT_NAME}/PlanetSurface.cpp
    src/${PROJECT_NAME}/PlanetCoordinateSystem.h    src/${PROJECT_NAME}/PlanetCoordinateSystem.cpp
    src/${PROJECT_NAME}/PlanetTextureGenerator.h    src/${PROJECT_NAME}/PlanetTextureGenerator.cpp
    src/${PROJECT_NAME}/SurfaceConfig.h
    src/${PROJECT_NAME}/utils.h
    src/${PROJECT_NAME}/types.h
)

set(SRC_VENDOR_STB
    src/vendor/stb/stb_image.h
)

source_group("TerrainLib" FILES
    ${SRC_TERRAINLIB}
)

source_group("vendor/stb" FILES
    ${SRC_VENDOR_STB}
)

add_library(${PROJECT_NAME} SHARED # Creating a shared (*.dll) library named by project name
    ${SRC_TERRAINLIB}              # and created form "SOURCES" and "INCLUDES" source files.
    ${SRC_VENDOR_STB}
)

add_library(${PROJECT_NAME}::${PROJECT_NAME} ALIAS ${PROJECT_NAME})

target_link_libraries(${PROJECT_NAME}
    geGL
    geUtil
    glm
)

target_include_directories(${PROJECT_NAME}                          # Including files from src directory to project, so compiler will
  PUBLIC src                                                        # be able to include necessary header files.
)

find_file(textureImage
    earth_cube_map.png
    HINTS ${${APP_NAME}_RESOURCES}
)

target_compile_definitions(${PROJECT_NAME} PUBLIC
    "EARTH_CUBE_MAP_PNG=\"${textureImage}\""
    $<$<CONFIG:DEBUG>:"TL_DEBUG">
)

option(${PROJECT_NAME}_BUILD_TESTS "toggle building of unit tests") # Setting an option for user of cmake to build project with unit tests.
if(${PROJECT_NAME}_BUILD_TESTS)                                     # Condition if option specified above is set to ON.
  enable_testing()                                                  # Enable cmake testing framework.
  add_subdirectory(tests)                                           # Add subdirectory with cmake project with unit test and corresponding cmake.
  add_test(NAME baseTest COMMAND tests)                             # Adding cmake tests from project added above to cmake testing framework.
endif()                                                             # End of condition.

##############################################################################################################################
# Here is generation of (OnWindows-necessary) makra definitions for exporting symbols from shared (*.dll) library
# Custom variant of "set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)" command
##############################################################################################################################

set(PROJECT_NAME_LOWER)                                             # Setting a variable where lowered version of project name will be stored.
string(TOLOWER ${PROJECT_NAME} PROJECT_NAME_LOWER)                  # Storing a lowered project name to "PROJECT_NAME_LOWER" variables.

include(GenerateExportHeader)                                       # Including library with following "generate_export_header" function.
generate_export_header(${PROJECT_NAME}                              # Generating header file with makra definitions with specified full filename.
  EXPORT_FILE_NAME ${PROJECT_NAME}/${PROJECT_NAME_LOWER}_export.h
)
