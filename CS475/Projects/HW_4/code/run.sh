#!/usr/bin/zsh

icpc -o proj project_4.c -O3 -lm -openmp -align -no-vec
./proj
