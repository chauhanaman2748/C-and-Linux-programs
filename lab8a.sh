#!/bin/bash

# Check if sample.txt is present in the current directory
if [ ! -f "sample.txt" ]; then
  echo "Sample.txt not present, file created..."
  # If sample.txt does not exist, create the file
  touch sample.txt

# Check if you are the owner of the file
elif [ $(stat -c %U sample.txt) == $USER ]; then
  # If you are the owner, check if the file has write permission
  if [ -w "sample.txt" ]; then
    # If the file has write permission, append the contents of ls -1 into sample.txt
    ls -1 >> sample.txt
  else
    # If the file has no write permission, set the write permission of the file using chmod
    echo "No write permission for sample.txt"
    chmod u+w sample.txt
    echo "Write permission added to sample.txt"
    ls -1 >> sample.txt
    echo "ls -1 command appended in sample.txt"
  fi
else
  # If you are not the owner, output an appropriate message
  echo "You are not the owner of sample.txt"
fi

