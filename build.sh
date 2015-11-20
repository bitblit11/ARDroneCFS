#!/bin/bash
git submodule update --init --recursive
cd config/softsim
mkdir build
cd build
rm -Rf *
cmake ..
make

