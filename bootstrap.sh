#!/bin/sh

pwd=$(pwd)
base_dir="$pwd/.build-deps"
tmp_dir="$base_dir/tmp"
bin_dir="$base_dir/bin"

export PATH="$bin_dir:$PATH"

cmake_version="3.1.0"
cmake_bin="$base_dir/bin/cmake"
install_cmake="$pwd/scripts/install-cmake.sh"

if [ ! -d $tmp_dir ]; then
    mkdir $tmp_dir -p
fi

if [ ! -f $cmake_bin ]; then
    $install_cmake --version $cmake_version --install-path $base_dir --download-path $tmp_dir
fi
