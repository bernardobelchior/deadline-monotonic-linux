#!/bin/bash

DIR_PATH=$(realpath "$1")
CUR_PATH=$(realpath .)

echo "Searching in $DIR_PATH"

find "$DIR_PATH/kernel" -maxdepth 1 -type d &> /dev/null
if [ $? -ne 0 ]; then
	echo "Path has no directory 'kernel'. Exiting.."
	exit 1
fi

NEW_FILES=$(find "./kernel" -type f | cut -b 10-)

while read -r filename; do
	new_filename=$(echo "$DIR_PATH/kernel/$filename")
	if [[ -f "$new_filename" && ! -L "new_filename" ]]; then
		#mv "$new_filename" "$new_filename.old"
		echo "File $new_filename renamed to $new_filename.old"
	fi

	ln -s -f "$CUR_PATH/kernel/$filename" "$new_filename"
	echo "Created symlink from $CUR_PATH/kernel/$filename to $new_filename"
done <<< "$NEW_FILES"
