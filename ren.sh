#!/bin/bash

# Ensure script is run with sudo
if [ "$EUID" -ne 0 ]; then
  echo "Please run as root"
  exit
fi

# Function to rename files, directories, and content inside files
rename_files_and_content() {
  local dir="$1"
  
  # Rename files and directories (nrgc -> nrgc)
  find "$dir" -depth -name '*nrgc*' | while IFS= read -r file; do
    newname=$(echo "$file" | sed -e 's/nrgc/nrgc/g' -e 's/ENERGYCOIN/ENERGYCOIN/g' -e 's/Nrgc/Nrgc/g' -e 's/NRGC/NRGC/g')
    mv "$file" "$newname"
  done

  # Replace all content inside files
  grep -rl 'nrgc\|ENERGYCOIN\|Nrgc\|NRGC' "$dir" | while IFS= read -r file; do
    sudo sed -i 's/nrgc/nrgc/g' "$file"
    sudo sed -i 's/ENERGYCOIN/ENERGYCOIN/g' "$file"
    sudo sed -i 's/Nrgc/Nrgc/g' "$file"
    sudo sed -i 's/NRGC/NRGC/g' "$file"
  done
}

# Set the directory to your Nrgccoin fork (change the path if needed)
TARGET_DIR="/home/ahodarcovs/Energycoin"

# Start renaming recursively
rename_files_and_content "$TARGET_DIR"

echo "Renaming completed!"
