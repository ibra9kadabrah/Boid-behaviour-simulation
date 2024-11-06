# Boid Behaviour Simulation

A simple program using raylib to demonstrate boid behavior. based on the original boids-algorithm
https://vanhunteradams.com/Pico/Animal_Movement/Boids-algorithm.html
article only contains psuedocode

I built this project in order to understand emergent behaviour, which I find quite fascinating.

## Prerequisites

- CMake (version 3.15 or higher)
- vcpkg package manager

## Installation

1. First, install vcpkg and of course clone this repo:
```bash
# Clone vcpkg
git clone https://github.com/Microsoft/vcpkg.git ~/vcpkg

# Run the bootstrap script
cd ~/vcpkg
./bootstrap-vcpkg.sh

# Add vcpkg to your path (add to your .bashrc). based on where you downloaded vcpkg of course
export VCPKG_ROOT=~/vcpkg
export PATH=$VCPKG_ROOT:$PATH
```

2. Install raylib with vcpkg as well as glfw3:
```bash
vcpkg install raylib:x64-linux
vcpkg install glfw3:x64-linux
```

Create build directory and build:
```bash
mkdir build
cd build
cmake .. -DCMAKE_TOOLCHAIN_FILE=$VCPKG_ROOT/scripts/buildsystems/vcpkg.cmake // or whatever is your path
make
```

run > ./my_game
