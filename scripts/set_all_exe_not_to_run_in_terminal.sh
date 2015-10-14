#!/bin/bash
# store all .pro.user file names in one array
files=(`ls -al .. | grep '.pro.user$'  | awk '{ for(i=9;i<=NF;i++) {printf("%s",$i) ;if (i!=NF) {printf(" ")} else {printf("\n")}} }'`)
file_num=${#files[@]}

for ((i = 0; i<file_num; i++))
do
	file_name=../${files[$i]}
	if  [ ! -e "$file_name" ] ; then
		echo "can not open file $file_name"
		break 
	fi
	echo $file_name
	sed -i.sed_bak s/UseTerminal\"\>true/UseTerminal\"\>false/g $file_name
	rm $file_name.sed_bak
done
