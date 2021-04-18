#
# Check ARGoS
#
find_package(ARGoS REQUIRED)
include_directories(${ARGOS_INCLUDE_DIRS})
link_directories(${ARGOS_LIBRARY_DIR})
link_libraries(${ARGOS_LDFLAGS})
string(REPLACE "/lib/argos3" "" ARGOS_PREFIX "${ARGOS_LIBRARY_DIR}")
set(CMAKE_INSTALL_PREFIX ${ARGOS_PREFIX} CACHE STRING "Install path prefix, prepended onto install directories." FORCE)

#
# Check Buzz
#
find_package(Buzz)
if(BUZZ_FOUND)
  include_directories(${BUZZ_C_INCLUDE_DIR})
endif(BUZZ_FOUND)
