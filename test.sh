#!/bin/bash

INPUT=`cmake --version`
SUBSTRING=$(echo $INPUT| cut -d' ' -f 3)

echo "cmake_minimum_required(VERSION $SUBSTRING)"
CMAKE_VERSION="cmake_minimum_required(VERSION $SUBSTRING)"
	
lineNo=1
sed -i "${lineNo}s/.*/$CMAKE_VERSION/" CMakeLists.txt
