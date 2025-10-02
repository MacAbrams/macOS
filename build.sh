#!/bin/bash

PROJECTS="libc kernel"

for PROJECT in $PROJECTS; do
	cd $PROJECT
	make all
	cd ..
done
