#!/bin/bash

if [ ! -d "build" ]; then
    mkdir build
    cd build
    cmake ..
    make
    cd ..
else
    cd build
    make
    cd ..
fi
