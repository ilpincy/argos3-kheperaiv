#
# Find the ARGoS package
#
find_package(PkgConfig)
pkg_check_modules(ARGOS REQUIRED argos3_${ARGOS_BUILD_FOR})
set(ARGOS_PREFIX ${ARGOS_PREFIX} CACHE INTERNAL "")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${ARGOS_PREFIX}/share/argos3/cmake)
set(CMAKE_INSTALL_PREFIX ${ARGOS_PREFIX} CACHE STRING "Install path prefix, prepended onto install directories." FORCE)

#
# Check whether all the necessary libs have been installed to compile the
# code that depends on Qt and OpenGL
#
if(ARGOS_BUILD_FOR_SIMULATOR)
  include(ARGoSCheckQTOpenGL)
endif(ARGOS_BUILD_FOR_SIMULATOR)

#
# Check for PThreads
# It is required only when compiling for the real robot
#
if(ARGOS_BUILD_FOR STREQUAL "khiv")
  find_package(Pthreads)
  if(NOT PTHREADS_FOUND)
    message(FATAL_ERROR "Required library pthreads not found.")
  endif(NOT PTHREADS_FOUND)
  add_definitions(${PTHREADS_DEFINITIONS})
  include_directories(${PTHREADS_INCLUDE_DIR})
endif(ARGOS_BUILD_FOR STREQUAL "khiv")

#
# Find Lua
#
find_package(Lua REQUIRED)
include_directories(${LUA_INCLUDE_DIR})

find_package(Buzz)
if(BUZZ_FOUND)
  include_directories(${BUZZ_C_INCLUDE_DIR})
endif(BUZZ_FOUND)

#
# Set ARGoS include dir
#
include_directories(${CMAKE_SOURCE_DIR} ${ARGOS_INCLUDE_DIRS})

#
# Set ARGoS link dir
#
link_directories(${ARGOS_LIBRARY_DIRS})
