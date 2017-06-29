# ARGoS3 - Khepera IV integration #

This repository contains the code that integrates the [ARGoS3 multi-robot simulator](http://www.argos-sim.info) and the [Khepera IV robot](https://www.k-team.com/khepera-iv).

This code allows you to simulate the Khepera IV in ARGoS3, and to run ARGoS3 controllers on the real Khepera IV.

# Compilation Instructions #

## To Simulate The Khepera IV in ARGoS3 ##

    $ mkdir build_sim
    $ cd build_sim
    $ cmake -DCMAKE_BUILD_TYPE=Release ../src
    $ make
    $ sudo make install
    
## To Run ARGoS3 Code on the Khepera IV ##

First, you need to install the [light toolchain provided by K-Team](http://ftp.k-team.com/KheperaIV/software/Gumstix%20COM%20Y/light_tools/poky-glibc-i686-khepera4-image-cortexa8hf-vfp-neon-toolchain-1.8.sh).

Next, run these commands:

    $ mkdir build_khiv
    $ cd build_khiv
    $ cmake -DCMAKE_TOOLCHAIN_FILE=../src/cmake/KheperaIV.cmake ../src
    $ make

This creates the libraries that connect your controller to the Khepera IV code. You need to install them on the robot in a convenient location.
