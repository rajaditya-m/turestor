#!/bin/bash
# store all .pro.user file names in one array
exes_cmake=../cmake_config/exes.cmake
modules_cmake=../cmake_config/modules.cmake
cmd="ls -l ../exe_src | grep '^d' | grep -v 'library' | awk '{print \$NF}'"
echo "set(exes" > $exes_cmake
eval "$cmd" >> $exes_cmake
echo ")" >> $exes_cmake
echo "# exe folders"
cat $exes_cmake

echo "# src folders"
echo "#--------------------------"
cmd="ls -l ../src | grep '^d' | awk '{print \$NF}'"
echo "set(modules" > $modules_cmake
eval "$cmd" >> $modules_cmake
echo ")" >> $modules_cmake
cat $modules_cmake

