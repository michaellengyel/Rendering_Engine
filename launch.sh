#! /bin/sh

# Configure
cmake -DGLFW_BUILD_DOCS=OFF -S . -B build

# Build
cd build ; make

# Run
./Rendering_Engine