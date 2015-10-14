#!/bin/bash
output_files() {
	files=(`eval $1`)
	file_num=${#files[@]}
	for ((i = 0; i<file_num; i++))
	do
	  echo '  $$PWD/'"${files[$i]} \\" >> $2.pri
	done
  echo "" >> $2.pri
}

if [ "$#" -ne 1 ]; then
  echo "incorrect argument"
  exit
fi

current_dir=$PWD
dir=../src/$1
if [ ! -e $dir ]; then
  mkdir $dir 
fi

cd $dir
# header files
echo 'INCLUDEPATH += $$PWD' > $1.pri
echo 'HEADERS += \' >> $1.pri
glob_h_cmd="ls -l . | grep '.h$' | awk '{print \$NF}'"
output_files "$glob_h_cmd" $1
echo "heaer files:"
eval $glob_h_cmd
echo ""

# cpp files
echo 'SOURCES += \' >> $1.pri
glob_cpp_cmd="ls -l . | grep '.cpp$' | awk '{print \$NF}'"
output_files "$glob_cpp_cmd" $1
echo "cpp files:"
eval $glob_cpp_cmd
echo ""

# generate cmake file for the new folder
source $current_dir/cmake_gen.sh
gen_cmake_for_folder add_library

cd $current_dir

source new_exe.sh
insert_unique_line "../cmake_config/modules.cmake" $1 "set("
    # \\ causes problem
# insert_unique_line "../qmake_config/modules.pri" "$1 \\" "modules = "
