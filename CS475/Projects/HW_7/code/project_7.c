#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <omp.h>
#include <time.h>



#ifndef NUMT
#define NUMT           4
#endif
#ifndef NUMM
#define NUMM           4
#endif

// Globals
long long int NUMS = (NUMM * 1024);
long double *A = new long double[ NUMS ]; 
long double *B = new long double[ NUMS ];
long double *C = new long double[ NUMS ];



void DoMult( ) {
    const int share = NUMS / NUMT;
    int me = omp_get_thread_num( );
    int first = me * share;
    C[first:share] = A[first:share] * B[first:share];
}

int main( int argc, char *argv[ ] ) {
    double start_time, time;
    
    
    for (int i=0; i < NUMS; i++) {
        A[i] = B[i] = C[i] = (double)sqrt(i);
    }
#ifdef CEAN
    omp_set_num_threads( NUMT );
    start_time = omp_get_wtime();
    #pragma omp parallel
    {
        DoMult( );
    }
#else
    omp_set_num_threads( NUMT );
    start_time = omp_get_wtime();
    #pragma omp parallel for simd
    for( int i = 0; i < NUMS; i++ )
    {
        C[i] = A[i]*B[i];
    }  
#endif
    time = (omp_get_wtime() - start_time);

    printf("%f,", ((NUMS)/time)/1000000);
    return 0;
}
