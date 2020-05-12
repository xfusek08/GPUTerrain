
cmake_minimum_required(VERSION 3.15.0)

project(
  GeoPlanetLib
  VERSION 0.0.0
)

SET(CMAKE_DEBUG_POSTFIX           "d"  CACHE STRING "add a postfix, usually d on windows")
SET(CMAKE_RELEASE_POSTFIX         ""   CACHE STRING "add a postfix, usually empty on windows")
SET(CMAKE_RELWITHDEBINFO_POSTFIX  "rd" CACHE STRING "add a postfix, usually empty on windows")
SET(CMAKE_MINSIZEREL_POSTFIX      "s"  CACHE STRING "add a postfix, usually empty on windows")

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_INCLUDE_CURRENT_DIR_IN_INTERFACE ON)

if(NOT TARGET glm)
  find_package(glm REQUIRED)
endif()

add_library(${PROJECT_NAME} SHARED "")

set(PRIVATE_SOURCES
    # vendor header libraries
    src/vendor/PerlinNoise/PerlinNoise.hpp

    # headers
    src/${PROJECT_NAME}/Utils.h

    # source files

    # ./
    src/${PROJECT_NAME}/CoordinateSystem.cpp
    src/${PROJECT_NAME}/Region.cpp
    src/${PROJECT_NAME}/Surface.cpp
    src/${PROJECT_NAME}/SurfaceGenerator.cpp
    src/${PROJECT_NAME}/SurfacePosition.cpp
    src/${PROJECT_NAME}/TectonicPlate.cpp

    # ./modifiers
    src/${PROJECT_NAME}/modifiers/ElevationModifier.cpp
    src/${PROJECT_NAME}/modifiers/JitterModifier.cpp
    src/${PROJECT_NAME}/modifiers/ModifierVariable.cpp
    src/${PROJECT_NAME}/modifiers/SurfaceModifier.cpp
    src/${PROJECT_NAME}/modifiers/TectonicPlateModifier.cpp
)

set(PUBLIC_INCLUDES
    # ./
    src/${PROJECT_NAME}/CoordinateSystem.h
    src/${PROJECT_NAME}/CoordinateTypes.h
    src/${PROJECT_NAME}/Region.h
    src/${PROJECT_NAME}/Surface.h
    src/${PROJECT_NAME}/SurfaceGenerator.h
    src/${PROJECT_NAME}/SurfacePosition.h
    src/${PROJECT_NAME}/TectonicPlate.h

    # ./modifiers
    src/${PROJECT_NAME}/modifiers/ElevationModifier.h
    src/${PROJECT_NAME}/modifiers/JitterModifier.h
    src/${PROJECT_NAME}/modifiers/ModifierFactory.h
    src/${PROJECT_NAME}/modifiers/modifiers.h
    src/${PROJECT_NAME}/modifiers/ModifierType.h
    src/${PROJECT_NAME}/modifiers/ModifierVariable.h
    src/${PROJECT_NAME}/modifiers/SurfaceModifier.h
    src/${PROJECT_NAME}/modifiers/TectonicPlateModifier.h
)

# see: https://crascit.com/2016/01/31/enhanced-source-file-handling-with-target_sources/
target_sources(${PROJECT_NAME}
    PRIVATE ${PRIVATE_SOURCES}
    PUBLIC  ${PUBLIC_INCLUDES}
)

target_link_libraries(${PROJECT_NAME}
    PUBLIC glm
)

target_include_directories(${PROJECT_NAME}                          # Including files from src directory to project, so compiler will
    PUBLIC src                                                      # be able to include necessary header files.
)

target_compile_definitions(${PROJECT_NAME} PUBLIC
    $<$<CONFIG:DEBUG>:"GP_DEBUG">
)

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

# configuration inspired by: https://github.com/dormon/SDL2CPP/blob/master/CMakeUtils.cmake
set_property(TARGET ${PROJECT_NAME} PROPERTY INTERFACE_${PROJECT_NAME}_MAJOR_VERSION ${PROJECT_VERSION_MAJOR})
set_property(TARGET ${PROJECT_NAME} APPEND PROPERTY COMPATIBLE_INTERFACE_STRING ${PROJECT_NAME}_MAJOR_VERSION)

install(TARGETS ${PROJECT_NAME} EXPORT ${PROJECT_NAME}Targets
    LIBRARY  DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE  DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME  DESTINATION ${CMAKE_INSTALL_BINDIR}
    INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(
    FILES ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}/${PROJECT_NAME_LOWER}_export.h
    DESTINATION include
)

# https://stackoverflow.com/a/25933984
foreach (file ${PUBLIC_INCLUDES} )
    get_filename_component(dir ${file} DIRECTORY)
    if (${dir} STREQUAL src )
        set(dir )
    else()
        string(REPLACE src/ "" dir ${dir})
    endif()
    install(FILES ${file} DESTINATION include/${dir} )
endforeach()
