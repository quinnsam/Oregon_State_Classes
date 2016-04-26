#!/usr/bin/zsh

#echo "Threads,Slices,Time,Volume"
for Mode in FINES FINED COARS COARD
do
    echo "$Mode,2,32,128,256,512,1024" # > out.csv
    for NUMT in 1 2 4 8 16 32 64 128 256 512
    do
        echo -n $NUMT, #>> out.csv
        for NUMBODIES in 2 32 128 256 512 1024 
        do
            icpc -o proj project_2.c -O3 -lm -openmp -align -DNUMT=$NUMT -DNUMBODIES=$NUMBODIES -D$Mode -DNUMSTEPS=100 # -DTIME
            ./proj #>> out.csv
        done
        echo "" #>> out.csv
    done
done
