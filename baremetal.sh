#!/bin/bash

set -e

echo '> converting data'
python init.py

echo '> compiling'
gcc -Ofast compute.c -o compute

echo '> starting computation'
./compute

echo '> plotting'
python plot.py

echo '> done'
