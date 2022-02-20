#!/bin/bash

# Builds Ebe 
# If run as a root, it will also compy newly build ebe into /usr/bin/ebe
# If first argument is the word "debug", the build type will be for developers 
#
# @autor Marek Sedlacek
# @date February 2022
# All right reserved, see LICENSE file
#

# Source (-S) option for cmake
SOURCE=.
# Build (-B) option for cmake
BUILD=build
# Build type
BUILD_TYPE=Release

# Check if debug
if [[ "$1" == "debug" || "$1" == "Debug" || "$1" == "DEBUG" ]]
then
    BUILD_TYPE=Debug
    echo "Building for Debug"
fi

# CMake
cmake -DCMAKE_BUILD_TYPE=$BUILD_TYPE -S $SOURCE -B $BUILD && cmake --build $BUILD --target ebe

# Try moving to /usr/bin
if cp $BUILD/ebe /usr/bin/ebe
then
    echo "Moved Ebe to /usr/bin/ebe. You can now use 'ebe' as a command."
else 
    echo "Could not move Ebe to /usr/bin/, try running script as a root."
fi
