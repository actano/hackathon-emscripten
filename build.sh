#!/usr/bin/env bash
set -o pipefail
# export EMSCRIPTEN=${HOME}/projects/emscripten/emsdk-portable/emscripten/1.37.22
# export OXYGINE=${HOME}/projects/oxygine/oxygine-framework

mkdir -p build
cd build
python ${OXYGINE}/tools/others/embed_folder_js.py -s ../data
cmake -DCMAKE_TOOLCHAIN_FILE="${EMSCRIPTEN}/cmake/Modules/Platform/Emscripten.cmake" ..
make
cd ..
