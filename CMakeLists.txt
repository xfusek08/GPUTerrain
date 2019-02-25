#
# Author: Petr Fusek
#

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

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_INCLUDE_CURRENT_DIR_IN_INTERFACE ON)

add_library(${PROJECT_NAME} SHARED ${SOURCES} ${INCLUDES})          # Creating a shared (*.dll) library named by project name
                                                                    # and created form "SOURCES" and "INCLUDES" source files.

target_include_directories(${PROJECT_NAME}                          # Including files from src directory to project, so compiler will
  PUBLIC src                                                        # be able to include necessary header files.
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
