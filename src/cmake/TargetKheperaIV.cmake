# The KheperaIV is seen as generic Linux distribution
set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_SYSTEM_PROCESSOR arm)

# The root directory of the toolchain
set(CMAKE_SYSROOT /opt/poky/1.8/sysroots/cortexa8hf-vfp-neon-poky-linux-gnueabi)

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
set(ARGOS_BUILD_FOR "khiv")
set(ARGOS_BUILD_NATIVE OFF)
set(ARGOS_DOCUMENTATION OFF)
set(ARGOS_INSTALL_LDSOCONF OFF)
set(ARGOS_USE_DOUBLE OFF)
