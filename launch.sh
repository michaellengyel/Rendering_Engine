#! /bin/sh

# Configure
cmake -S . -B build

# Build
cd build ; make

# Run
./Rendering_Engine