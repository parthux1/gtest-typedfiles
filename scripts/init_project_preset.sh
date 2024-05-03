#!/bin/bash

# script for initializing a new project with this preset
# flags:
# -p project_name to be set in CMakeLists.txt, readme.md and Doxyfile
# -d description to be set in CMakeLists.txt, readme.md and Doxyfile

while getopts p:d: flag
do
  case "${flag}" in
    p) project_name=${OPTARG};;
    d) project_description=${OPTARG};;
    ?) echo "> HELP: provide both -p project_name -d project_description";;
    *) echo "> invalid flag ${flag} ignored";;

  esac
done

# error handling
if [ -z "$project_name" ]
then
  echo "> project name not provided, exiting"
  exit 1
fi

if [ -z "$project_description" ]
then
  echo "> project description not provided, exiting"
  exit 1
fi

echo "> project name: $project_name";
echo "> description : $project_description";

# all files to sed
files_to_edit=("CMakeLists.txt" "readme.md" "doc/Doxyfile");

# apply changes
sed -i "s/<project_name>/\"$project_name\"/g" "${files_to_edit[@]}"
sed -i "s/<project_description>/\"$project_description\"/g" "${files_to_edit[@]}"