#
# File: GeoPlanetLib/CMakeLists.txt
# Original file: https://github.com/dormon/SDL2CPP/blob/master/CMakeLists.txt
# Author: Petr Fusek
#
# This file serves for proper cmake configuration with usage of "CMakeUtils.cmake"
# To generate GeoPlanetLib project as shared library provided by cmake paskage
#

cmake_minimum_required(VERSION 3.15)

project(
    GeoPlanetLib
    VERSION 0.0.0
)

#set these variables to *.cpp, *.c, ..., *.h, *.hpp, ...
set(SOURCES
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
set(PRIVATE_INCLUDES
    # headers
    src/${PROJECT_NAME}/Utils.h
)
set(PUBLIC_INCLUDES
    # vendor header libraries
    src/vendor/PerlinNoise/PerlinNoise.hpp

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
set(INTERFACE_INCLUDES )

#list of libraries to find
#it should contain list of "lists"
#format:
#set(ExternLibraries
#  A\\ B\\ C\\ D
#  E\\ F\\ G
#  )
#It will be converted into:
#find_package(A B C D)
#find_package(E F G)
#If version is specified, it has to be the second parameter (B)
set(ExternPrivateLibraries )
set(ExternPublicLibraries glm\\ REQUIRED)
set(ExternInterfaceLibraries )

#set these variables to targets
set(PrivateTargets )
set(PublicTargets glm)
set(InterfaceTargets )

#set these libraries to variables that are provided by libraries that does not support configs
set(PrivateIncludeVariables )
set(PublicIncludeVariables )
set(InterfaceIncludeVariables )
set(PrivateReleaseLibraryVariables )
set(PublicReleaseLibraryVariables )
set(InterfaceReleaseLibraryVariables )
set(PrivateDebugLibraryVariables )
set(PublicDebugLibraryVariables )
set(InterfaceDebugLibraryVariables )

include(CMakeUtils.cmake)

target_compile_definitions(${PROJECT_NAME} PUBLIC
    $<$<CONFIG:DEBUG>:"GP_DEBUG">
)
