#!/bin/sh

pwd=$(pwd)
cmake_version="3.1.0"
cmake_base_dir="$pwd/.cmake"
cmake="$cmake_base_dir/bin/cmake"
install_cmake="$pwd/scripts/install-cmake.sh"

if [ ! -d $cmake_base_dir ]; then
    mkdir $cmake_base_dir -p
fi

if [ ! -f $cmake ]; then
    $install_cmake --version $cmake_version --install-path $cmake_base_dir
fi
