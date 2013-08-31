# Sample toolchain file for building for Windows from an Ubuntu Linux system.
#
# Typical usage:
#    1) install cross compiler: `sudo apt-get install mingw-w64 g++-mingw-w64`
#    2) cp cmake/Toolchain-Ubuntu-mingw32.cmake.sample ~/Toolchain-Ubuntu-mingw32.cmake
#    3) tweak toolchain values as needed
#    4) cd build
#    5) cmake -DCMAKE_TOOLCHAIN_FILE=~/Toolchain-Ubuntu-mingw32.cmake ..

# name of the target OS on which the built artifacts will run
# and the toolchain prefix
set(CMAKE_SYSTEM_NAME Windows)
set(TOOLCHAIN_PREFIX i586-mingw32msvc)

# cross compilers to use for C and C++
set(CMAKE_C_COMPILER ${TOOLCHAIN_PREFIX}-gcc)
set(CMAKE_CXX_COMPILER ${TOOLCHAIN_PREFIX}-g++)
set(CMAKE_RC_COMPILER ${TOOLCHAIN_PREFIX}-windres)

# here is the target environment located
set(CMAKE_FIND_ROOT_PATH /usr/${TOOLCHAIN_PREFIX})

# search for programs in the build host directories
SET(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
# for libraries and headers in the target directories
SET(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
SET(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)