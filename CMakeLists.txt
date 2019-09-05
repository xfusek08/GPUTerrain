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

set(SRC_TERRAINLIB
    src/${PROJECT_NAME}/Terrain.h       src/${PROJECT_NAME}/Terrain.cpp
    src/${PROJECT_NAME}/TerrainFace.h   src/${PROJECT_NAME}/TerrainFace.cpp
    src/${PROJECT_NAME}/Mesh.h
)

source_group("TerrainLib" FILES
    ${SRC_TERRAINLIB}
)

SET(CMAKE_DEBUG_POSTFIX           "d"  CACHE STRING "add a postfix, usually d on windows")
SET(CMAKE_RELEASE_POSTFIX         ""   CACHE STRING "add a postfix, usually empty on windows")
SET(CMAKE_RELWITHDEBINFO_POSTFIX  "rd" CACHE STRING "add a postfix, usually empty on windows")
SET(CMAKE_MINSIZEREL_POSTFIX      "s"  CACHE STRING "add a postfix, usually empty on windows")

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_INCLUDE_CURRENT_DIR_IN_INTERFACE ON)

add_library(${PROJECT_NAME} SHARED ${SRC_TERRAINLIB})               # Creating a shared (*.dll) library named by project name
                                                                    # and created form "SOURCES" and "INCLUDES" source files.
add_library(${PROJECT_NAME}::${PROJECT_NAME} ALIAS ${PROJECT_NAME})

target_link_libraries(${PROJECT_NAME}
    geGL
    geUtil
    glm
)

target_include_directories(${PROJECT_NAME}                          # Including files from src directory to project, so compiler will
  PUBLIC src                                                         # be able to include necessary header files.
)

target_compile_definitions(${PROJECT_NAME} PUBLIC
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
