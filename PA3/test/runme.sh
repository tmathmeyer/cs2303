#!/bin/bash
cd ../
make && make clean
./life 10 10 20 tests/test2
./life 50 50 4 tests/test2

./life 100 100 2000 tests/pentomino