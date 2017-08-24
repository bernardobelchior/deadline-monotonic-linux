#!/bin/bash

DIR_PATH=$(realpath "$1")
CUR_PATH=$(realpath .)

cp "kcompile.sh" "$DIR_PATH/.."

# len(./src) = 7
NEW_FILES=$(find "./src" -type f | cut -b 7-)
NEW_DIRS=$(find "./src" -type d | cut -b 7-)

# Creates missing directories
while read -r dirname; do
	echo "Creating dir $DIR_PATH/$dirname"
	mkdir -p "$DIR_PATH/$dirname"
done <<< "$NEW_DIRS"

# Links files from repo to DIR_PATH
while read -r filename; do
	new_filename=$(echo "$DIR_PATH/$filename")
	if [[ -f "$new_filename" && ! -L "new_filename" ]]; then
		mv -nu "$new_filename" "$new_filename.old"
		echo "File $new_filename renamed to $new_filename.old"
	fi

	ln -s -f "$CUR_PATH/src/$filename" "$new_filename"
	echo "Created symlink from $CUR_PATH/src/$filename to $new_filename"
done <<< "$NEW_FILES"
