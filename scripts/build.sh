#!/usr/bin/env bash
set -Eeuo pipefail
IFS=$'\n\t'

# go to repo root
cd "${0%/*}/.."

mkdir -p build/ && cd build/
CC=clang CXX=clang++ cmake $@ ..
make -j4
cd ../
