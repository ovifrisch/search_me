#!/bin/bash

make
if [ $1 -eq 1 ]
then
	./search_me clean
else
	./search_me
fi
