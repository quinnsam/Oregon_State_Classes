#!/usr/bin/zsh
echo ",1,2,4,6,8,10,16,24,32,46,64,128" #,256,512,1024,2048,4096" # > out.csv
for NUML in 2 32 128 256 512 1024 
do
    echo -n "$NUML," 
    for NUMG in 1 2 4 6 8 10 16 24 32 46 64 128 #256 512 1024 2048 4096
    do
        icpc -o proj project_5.cpp -no-vec `pwd`/CL/libOpenCL.so -lm -openmp -DNUM_ELEMENTS=$(($NUMG*1024*1024)) -DLOCAL_SIZE=$NUML 
        ./proj #>> out.csv
    done
    echo "" #>> out.csv
done
