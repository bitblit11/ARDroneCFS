#!/bin/bash
mkdir -p build
cd build
rm -Rf *
cmake ..
make

