#!/bin/bash

# Check if both arguments are passed
if [ $# -eq 0 ] || [ $# -gt 2 ]; then
  echo "Usage: $0 <directory> [<extension>]"
  exit 1
fi

# Get the directory path and extension from the input arguments
directory=$1
extension=$2

# Set the default extension if it is not provided
if [ -z "$extension" ]; then
  extension="*"
fi

# Count the number of files with the specified extension in the directory
count=$(find "$directory" -maxdepth 1 -type f -name "*.$extension" | wc -l)

# Display the count of files with the specified extension
echo "The total number of .$extension files in $directory is: $count"
