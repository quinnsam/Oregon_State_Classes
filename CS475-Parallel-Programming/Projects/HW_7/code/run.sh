#!/usr/bin/zsh

echo "CEAN,2,32,128,256,512,1024,2048" # > out.csv
for NUMT in 1 2 4 8 16 32 64 128 256 512
do
    echo -n $NUMT, #>> out.csv
    for NUMM in 2 32 128 256 512 1024 2048
    do
        icpc -o proj project_7.c -O3 -lm -openmp -align -no-vec -DCEAN -DNUMT=$NUMT -DNUMM=$NUMM
        ./proj
    done
    echo "" #>> out.csv
done


echo "SIMD,2,32,128,256,512,1024,2048" # > out.csv
for NUMT in 1 2 4 8 16 32 64 128 256 512
do
    echo -n $NUMT, #>> out.csv
    for NUMM in 2 32 128 256 512 1024 2048
    do
        icpc -o proj project_7.c -O3 -lm -openmp -align -no-vec -DNUMT=$NUMT -DNUMM=$NUMM
        ./proj
    done
    echo "" #>> out.csv
done
