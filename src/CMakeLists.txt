#
# Set minimum required version
#
cmake_minimum_required(VERSION 3.5.1)

#
# Project name
#
project(argos3_${ARGOS_BUILD_FOR})

#
# Set build options
#
include(${CMAKE_SOURCE_DIR}/cmake/ARGoSBuildOptions.cmake)

#
# Deactivate RPATH for MacOSX
#
set(CMAKE_MACOSX_RPATH 0)

#
# Set the path additional cmake files must be searched for
#
set(CMAKE_MODULE_PATH $ENV{CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/cmake)

#
# Set CMake policies to select wanted behaviors
#
# Use new policies introduced up to this version
cmake_policy(VERSION 2.8.12)
if(POLICY CMP0042)
  cmake_policy(SET CMP0042 NEW)
endif(POLICY CMP0042)

#
# Include path points to the base source dir
#
include_directories(${CMAKE_SOURCE_DIR} ${CMAKE_BINARY_DIR})

#
# Make sure we are under Unix
#
if(NOT UNIX)
  message(FATAL_ERROR "ARGoS compiles only under UNIX, sorry!")
endif(NOT UNIX)

#
# Set compiler flags
#
include(${CMAKE_SOURCE_DIR}/cmake/ARGoSBuildFlags.cmake)

#
# Check for libraries
#
include(${CMAKE_SOURCE_DIR}/cmake/ARGoSBuildChecks.cmake)

#
# Set up CPack for later use
#
include(${CMAKE_SOURCE_DIR}/cmake/ARGoSPackaging.cmake)

#
# Compile stuff
#
add_subdirectory(plugins)
add_subdirectory(testing)
