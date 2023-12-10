#!/usr/bin/bash

# Run make to build test
make

# Run bright.exe
./bright yispTest.lisp >> yispResults.txt

# Pause to see output before exiting
read -p "Press enter to exit"