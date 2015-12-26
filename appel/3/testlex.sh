#!/bin/sh

for f in $(ls ../test)
do
	echo "Checking $f ..."
	./lextest "../test/$f" | grep "illegal token"
done
