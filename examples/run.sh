#! /bin/bash

# Check if build directory exists
if [ ! -d "build" ]; then
    echo "Build directory does not exist. Creating it now..."
    mkdir build
    meson setup build
fi

# Compile and run
meson compile -C build && ./build/sdl_example