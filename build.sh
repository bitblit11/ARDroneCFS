#!/bin/bash
git submodule update --init --recursive
(cd Sage; ./build.sh)

