#!/bin/bash

# Check the number of command-line arguments
if [ "$#" -ne 1 ]; then
    echo "Usage: $0 <pid_max_path>"
    exit 1
fi

# Get the path to the pid_max file from the command-line argument
pid_max_path="$1"

# Check if the provided path exists
if [ ! -e "$pid_max_path" ]; then
    echo "Error: File $pid_max_path not found"
    exit 1
fi

# Read the maximum PID value from the pid_max file
pid_max=$(cat "$pid_max_path")

# Print the maximum PID value
echo "Maximum Process ID (PID) Value: $pid_max"

