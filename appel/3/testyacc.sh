#!/bin/sh

for f in $(ls ../test)
do
	./parsetest "../test/$f"
done

echo "WARNING: parsing should fail in tiger49.tig!"
