#!/bin/sh

# Check if both arguments are provided
if [ $# -ne 2 ]; then
    echo "Error: Two arguments required - <writefile> and <writestr>"
    exit 1
fi

writefile=$1
writestr=$2

# Extract directory path from writefile
dirname=$(dirname "$writefile")

# Create the directory if it does not exist
if [ ! -d "$dirname" ]; then
    mkdir -p "$dirname" || {
        echo "Error: Failed to create directory $dirname"
        exit 1
    }
fi

# Write the string to the file (overwrite if exists)
echo "$writestr" > "$writefile" || {
    echo "Error: Failed to write to file $writefile"
    exit 1
}

echo "File created successfully: $writefile"
exit 0
