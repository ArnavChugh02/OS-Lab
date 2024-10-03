source_file="$1"
destination_file="$2"

cp "$source_file" "$destination_file"

if [ $? -eq 0 ]; then
    echo "File successfully copied."
else
    echo "Error: Failed to copy file."
    exit 1
fi

