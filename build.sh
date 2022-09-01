#!/bin/bash

cur_path=`pwd`

cd ${cur_path}

build_dir=${cur_path}/build

if [ "$1" = "clean" ]; then
    rm -rf ${build_dir}
    exit 0
fi

if [ ! -d ${build_dir} ]; then
    mkdir -p ${build_dir}
fi

cd ${build_dir}

cmake ..
make
