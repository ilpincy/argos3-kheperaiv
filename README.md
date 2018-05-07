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

Next, you need to designate a folder where you'll install all the ARGoS-related binaries. Let's call this folder `${INSTALLPREFIX}`. Make sure the folder exists and it is writable by your user:

    $ mkdir -p ${INSTALLPREFIX}

To make ARGoS controllers work on the Khepera IV, you need to crosscompile the ARGoS core and the Khepera IV plugin. In the following, we will assume that you have three directories:

| Variable        | Meaning                                     |
|-----------------|---------------------------------------------|
| `INSTALLPREFIX` | Where the compile code is installed         |
| `ARGOS3PATH`    | Where the ARGoS3 core code is stored        |
| `KHIVPATH`      | Where the the code of this plugin is stored |

### Crosscompiling the ARGoS core ###

To compile the ARGoS core for the Khepera IV, follow these instructions:

    $ cd ${ARGOS3PATH}
    $ mkdir build_khiv
    $ cd build_khiv
    $ cmake -DCMAKE_TOOLCHAIN_FILE=${KHIVPATH}/src/cmake/TargetKheperaIV.cmake -DCMAKE_INSTALL_PREFIX=${INSTALLPREFIX} ../src
    $ make install

### Crosscompiling the Khepera IV plugin ###

To compile the Khepera IV plugin code, follow these instructions:

    $ export PKG_CONFIG_PATH=${INSTALLPREFIX}/lib/pkgconfig:${PKG_CONFIG_PATH}
    $ cd ${KHIVPATH}
    $ mkdir build_khiv
    $ cd build_khiv
    $ cmake -DCMAKE_TOOLCHAIN_FILE=${KHIVPATH}/src/cmake/TargetKheperaIV.cmake -DCMAKE_INSTALL_PREFIX=${INSTALLPREFIX} ../src
    $ make install

