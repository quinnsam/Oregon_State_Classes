#!/usr/bin/zsh

echo "Fix_1"
echo " ,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16" #> out.csv
for NUMT in 1 2 4 8 16
do
    echo -n $NUMT, #>> out.csv
    for NUM in {0..16} 
    do
        g++ -o proj project_3.c -lm -fopenmp -DNUM=$NUM -DNUMT=$NUMT -DFIX=1
        ./proj #>> out.csv
    done
    echo "" #>> out.csv
done

echo "Fix_2"
for NUMT in 1 2 4 8 16
do
    echo -n $NUMT, #>> out.csv
    g++ -o proj project_3.c -lm -fopenmp -DNUM=$NUM -DNUMT=$NUMT -DFIX=2
    ./proj #>> out.csv
done
