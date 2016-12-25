#!/bin/bash
echo -e "\tStart script"

echo -e "\tStart compile"
make
result_comlile=$?

if (( $result_comlile == 0 ))
	then
	echo -e "\tStart programm: $1"
	./main
fi
