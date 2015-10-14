#!/bin/bash

# Usage:
# insert_unique_line file_to_insert line_to_insert line_after_which_to_insert
insert_unique_line() {
	file_to_insert="$1"
	inserted_line_no=`grep -i "$2" $file_to_insert |  wc -l`
	if [ $inserted_line_no -ne "0" ]; then
	    echo "line \"$2\" already exist in $file_to_insert"
	else
		tmp_file="tmp.log"
		cat $file_to_insert > $tmp_file
		line_no=`grep -ni "$3" $file_to_insert |  cut -f1 -d:`
    if [ $line_no -eq "0" ]; then
       echo "line $3 doesn't exist in file $file_to_insert"
    else
		  total_line_num=(`cat $tmp_file | wc -l`)
		  last_lines_num=$(($total_line_num - $line_no))
		  head -n $line_no $tmp_file > $file_to_insert
		  echo "$2" >> $file_to_insert
		  tail -n $last_lines_num $tmp_file >> $file_to_insert
		  cat $file_to_insert
		  rm $tmp_file
    fi
	fi
}

RUNNING="$(basename $0)"
if [[ "$RUNNING" == "new_exe.sh" ]]; then
    if [ "$#" -ne 1 ]; then
      echo "incorrect argument"
      exit
    fi

    current_dir=$PWD
    dir=../exe_src/$1
    if [ ! -e $dir ]; then
      echo "folder $dir does not exist. Create new folder and add template files"
      mkdir $dir
      cp $current_dir/exe_template/main.cpp $dir/$1.cpp
      cp $current_dir/exe_template/main.pro $dir/$1.pro
    fi

    cd $dir
    source $current_dir/cmake_gen.sh
    gen_cmake_for_folder add_executable 
    cd $current_dir
    insert_unique_line "../cmake_config/exes.cmake" $1 "set("
    # \\ causes problem
#    insert_unique_line "../qmake_config/subdirs.pri" "$1 \\" "exes ="
fi
