#!/bin/bash
#sample pattern "*/*.txt" all files under this directory with .txt suffix
SaveIFS="$IFS"
IFS=$'\n'
files_to_delete=(`find . -path "$1"`)
file_count=${#files_to_delete[@]}
# printf -- '%s\n' "${files_to_delete[*]}"
if [ $file_count -eq 0 ]
then
	echo "There no file with pattern $1." 
else 
	for((i=0; i<file_count; i++))
	do
		echo ${files_to_delete[$i]}
	done
	echo "There are $file_count files with pattern $1." 
	echo -n "Delete all of them ? [y/n] : "
	read answer
	if [ $answer == y ] 
	then
		for((i=0; i<file_count; i++))
		do
			rm  "${files_to_delete[$i]}"
		done
	fi
fi
IFS=${SaveIFS}
