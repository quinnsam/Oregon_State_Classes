#!/usr/bin/zsh

#echo "Threads,Slices,Time,Volume"
echo " ,2,32,128,256,512,1024,2048,4096,8192,16384,32768" > out.csv
for NUMT in 1 2 4 8 16 32 64 128 256 512 1024 2048
do
    echo -n $NUMT, >> out.csv
    for NUMS in 2 32 128 256 512 1024 2048 4096 8192 16384 32768 
    do
        g++ -o proj project_1.c -O3 -lm -fopenmp -DNUMS=$NUMS -DNUMT=$NUMT
        ./proj >> out.csv
    done
    echo "" >> out.csv
done
