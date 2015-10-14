#!/bin/bash
gen_cmake_for_folder() {
		h_file=(`ls -l  | grep 'h$'  | awk '{print $NF}'`)
		h_num=${#h_file[@]}
		cpp_file=(`ls -l  | grep 'cpp$'  | awk '{print $NF}'`)
		cpp_num=${#cpp_file[@]}
		# Qt UI file
		ui_file=(`ls -l  | grep 'ui$'  | awk '{print $NF}'`)
		ui_num=${#ui_file[@]}
		if [ "${h_num}" -eq "0" ] && [ "${cpp_num}" -eq "0" ] ; then
			cd ..
			continue
		fi
		dir_name=${PWD##*/}
		echo -n "" > CMakeLists.txt
		# header files
		if [ "${h_num}" -ne "0" ]; then
			echo 'set(headers' >> CMakeLists.txt
			for ((h = 0; h<h_num; h++))
			do
				echo "  ${h_file[$h]}" >> CMakeLists.txt
			done
			echo ")" >> CMakeLists.txt
			echo "" >> CMakeLists.txt
		fi
		# UI file
		if [ "${ui_num}" -ne "0" ]; then
			echo "SET(CMAKE_AUTOMOC ON)" >> CMakeLists.txt
			echo "QT5_WRAP_UI(ui_headers" >> CMakeLists.txt
			for ((u = 0; u<ui_num; u++))
			do
				echo "  ${ui_file[$u]}" >> CMakeLists.txt
			done
			echo ")" >> CMakeLists.txt
			echo "" >> CMakeLists.txt
		fi
		# cpp files
		if [ "${cpp_num}" -ne "0" ]; then
			echo 'set(sources' >> CMakeLists.txt
			for ((p = 0; p<cpp_num; p++))
			do
				echo "  ${cpp_file[$p]}" >> CMakeLists.txt
			done
			echo ")" >> CMakeLists.txt
			echo "" >> CMakeLists.txt
			echo 'ExtractLastPartFromFullPath(${CMAKE_CURRENT_LIST_DIR} dir_name)' >> CMakeLists.txt
			if [ "${ui_num}" -ne "0" ]; then
				# has .ui file
				echo "$1"'(${dir_name} ${headers} ${sources} ${ui_headers})' >> CMakeLists.txt
				echo -n 'target_link_libraries(${dir_name} ' >> CMakeLists.txt
				if [ $1 == "add_library" ]; then
					echo 'Qt5::Widgets Qt5::OpenGL)' >> CMakeLists.txt
				else
					echo '${LIBS})' >> CMakeLists.txt
				fi
			else
				echo "$1"'(${dir_name} ${headers} ${sources})' >> CMakeLists.txt
				if [ $1 == "add_executable" ]; then
					echo 'target_link_libraries(${dir_name} ${LIBS})' >> CMakeLists.txt
				fi
			fi
		fi
}

gen_subdir_cmake_file () {
	dir=(`eval $1`)
	linecount=${#dir[@]}
	for ((i = 0; i<linecount; i++))
	do
		cd "${dir[$i]}"
    gen_cmake_for_folder $2
		cd ..
	done
}

gen_exe_cmake() {
	echo "generate CMakeLists.txt file for executables"
	current_dir=${PWD}
	exe_src_dir="${PWD}/../exe_src"
	cd $exe_src_dir
	cmd="ls -l . | grep ^d | grep -v library | awk '{print \$NF}'"
	gen_subdir_cmake_file "$cmd" add_executable
	# exes_cmake="../cmake_config/exes.cmake"
	# echo "set(exes" > $exes_cmake
	# eval "$cmd" >> $exes_cmake
	# echo ")" >> $exes_cmake
	# eval "$cmd"
	cd $current_dir
}

gen_src_cmake() {
  echo "generate CMakeLists.txt file for module libraries"
	current_dir=${PWD}
	src_dir="${PWD}/../src"
	cd $src_dir
	cmd="ls -l . | grep "^d" | awk '{print \$NF}'"
	gen_subdir_cmake_file "$cmd" add_library 
	# modules_cmake="../cmake_config/modules.cmake"
	# echo "set(modules" > $modules_cmake
	# eval "$cmd" >> $modules_cmake
	# echo ")" >> $modules_cmake
	# eval "$cmd"
	cd $current_dir
}

RUNNING="$(basename $0)"
if [[ "$RUNNING" == "cmake_gen.sh" ]]; then
  gen_exe_cmake
  gen_src_cmake
  ./update_cmake_src.sh
  exit
fi

