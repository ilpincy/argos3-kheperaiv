# The KheperaIV is seen as generic Linux distribution
set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_SYSTEM_PROCESSOR arm)

# The root directory of the toolchain
set(CMAKE_SYSROOT /opt/poky/1.8/sysroots/cortexa8hf-vfp-neon-poky-linux-gnueabi)

# The root directory of the toolchain
set(CMAKE_MODULE_PATH
  /opt/poky/1.8/sysroots/cortexa8hf-vfp-neon-poky-linux-gnueabi/usr/share/argos3/cmake
  /opt/poky/1.8/sysroots/cortexa8hf-vfp-neon-poky-linux-gnueabi/usr/share/buzz/cmake)

# The architecture name
set(TOOLCHAIN_ROOT /opt/poky/1.8/sysroots/i686-pokysdk-linux/usr)

# Set compilation flags
set(CMAKE_C_FLAGS "-march=armv7-a -mfloat-abi=hard -mfpu=neon -mtune=cortex-a8 -O2 -pipe -g -feliminate-unused-debug-types -fPIC --sysroot=${CMAKE_SYSROOT}" CACHE STRING "Flags used by the compiler during all build types.")
set(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} -std=c++11" CACHE STRING "Flags used by the compiler during all build types.")
set(CMAKE_SHARED_LINKER_FLAGS "-Wl,-O1 -Wl,--hash-style=gnu -Wl,--as-needed -fPIC --sysroot=${CMAKE_SYSROOT}" CACHE STRING "Flags used by the linker during the creation of dll's.")
set(CMAKE_MODULE_LINKER_FLAGS ${CMAKE_SHARED_LINKER_FLAGS} CACHE STRING "Flags used by the linker during the creation of modules.")
set(CMAKE_STATIC_LINKER_FLAGS ${CMAKE_SHARED_LINKER_FLAGS} CACHE STRING "Flags used by the linker during the creation of static libraries.")
set(CMAKE_EXE_LINKER_FLAGS ${CMAKE_SHARED_LINKER_FLAGS} CACHE STRING "Flags used by the linker.")

# Paths to tools
if(CMAKE_VERSION VERSION_LESS "3.6")
  # Use old method to override compile checks, which fail
  include(CMakeForceCompiler)
  CMAKE_FORCE_C_COMPILER(${TOOLCHAIN_ROOT}/bin/arm-poky-linux-gnueabi/arm-poky-linux-gnueabi-gcc ARM-POKY)
  CMAKE_FORCE_CXX_COMPILER(${TOOLCHAIN_ROOT}/bin/arm-poky-linux-gnueabi/arm-poky-linux-gnueabi-g++ ARM-POKY)
  set (CMAKE_STRIP ${TOOLCHAIN_ROOT}/bin/arm-poky-linux-gnueabi/arm-poky-linux-gnueabi-strip)
else(CMAKE_VERSION VERSION_LESS "3.6")
  # Perform compiler checks passing flags
  set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)
endif(CMAKE_VERSION VERSION_LESS "3.6")

# Don't look for programs in the sysroot (they don't work locally)
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)

# Look for other stuff in the sysroot
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)

# ARGoS settings
set(ARGOS_BUILD_FOR "khiv" CACHE STRING "What is ARGoS being built for? \"simulator\" or a robot name (lowercase)")
set(ARGOS_BUILD_NATIVE OFF CACHE BOOL "ON -> compile with platform-specific optimizations, OFF -> compile to portable binary")
set(ARGOS_DYNAMIC_LIBRARY_LOADING OFF CACHE BOOL "ON -> compile support for dynamic library loading, OFF -> no support for dynamic library loading")
set(ARGOS_DOCUMENTATION OFF CACHE BOOL "ON -> compile documentation, OFF -> dont'compile documentation")
set(ARGOS_INSTALL_LDSOCONF OFF CACHE BOOL "ON -> install argos3.conf in /etc/ld.so.conf/, OFF -> don't")
set(ARGOS_USE_DOUBLE OFF CACHE BOOL "ON -> use double for Real, OFF -> use float for Real")
set(ARGOS_THREADSAFE_LOG OFF CACHE BOOL "ON -> compile thread-safe version of log, OFF -> compile thread-unsafe version of log")
