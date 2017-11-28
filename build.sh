#!/usr/bin/env bash
set -o pipefail
export EMSCRIPTEN=${HOME}/projects/emscripten/emsdk-portable/emscripten/1.37.22
OXYGINE=${HOME}/projects/oxygine/oxygine-framework

python ${OXYGINE}/tools/others/embed_folder_js.py -s ./data
mkdir -p build
cd build
cmake -DCMAKE_TOOLCHAIN_FILE="${EMSCRIPTEN}/cmake/Modules/Platform/Emscripten.cmake" ..
make
cd ..
