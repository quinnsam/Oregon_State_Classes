#!/usr/bin/zsh

echo ",1,2,4,6,8,10,16,24,32,46,64" # > out.csv
for NUMG in 1 2 4 6 8 10 16 24 32 46 64
do
    echo -n $NUMG, #>> out.csv
    for NUML in 2 32 128 256 512 1024 
    do
        icpc -o proj project_5.cpp -no-vec `pwd`/CL/libOpenCL.so -lm -openmp -DGLOB_WORK_GROUP=$NUMG -DLOC_WORK_GROUP=$NUML 
        ./proj #>> out.csv
    done
    echo "" #>> out.csv
done
