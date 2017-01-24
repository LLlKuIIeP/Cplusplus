#!/bin/bash
echo "Start script"

echo "Start compile"
make
result_comlile=$?

if (( $result_comlile == 0 ))
    then
    echo "Start programm: $1"
    ./main
fi
