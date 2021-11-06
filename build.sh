#!/bin/bash

if [ ! -d "build" ]; then
    mkdir build
    cd build
    cmake -G Ninja ..
    ninja
    cd ..
else
    cd build
    ninja
    cd ..
fi
