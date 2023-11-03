#!/bin/bash

folder_name="build"

if [ ! -d "$folder_name" ]; then
    mkdir "$folder_name"
    echo "Folder '$folder_name' created."
fi

gcc main.c -lraylib -o $folder_name/main

if [ $? -ne 0 ]; then
	echo "Build Failed"
	exit 1
fi

./$folder_name/main
