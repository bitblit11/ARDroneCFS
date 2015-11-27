#!/bin/bash
git submodule update --init --recursive
source setvars.sh
cd config/softsim
./build.sh
