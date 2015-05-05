#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

#ifndef NUMT
#define NUMT           4
#endif
#ifndef NUM
#define NUM            4
#endif

struct s
{
    float value;
#if FIX == 1
    int pad[ NUM ];
#endif
} Array[4];


int main( int argc, char *argv[ ] ) {
    double time0, time1, time;
#ifndef _OPENMP
	fprintf( stderr, "OpenMP is not available\n" );
	return 1;
#endif
    //. . .

    omp_set_num_threads( NUMT );

    unsigned int someBigNumber = 1000000000;        // if > 4B, use "long unsigned int"

	time0 = omp_get_wtime( );
#pragma omp parallel for
    for( int i = 0; i < 4; i++ )
    {
#if FIX == 2
        float tmp=Array[i].value;
        for( unsigned int j = 0; j < someBigNumber; j++ )
        {
            tmp = tmp + 2.;
        }
        Array[ i ].value = tmp;
#elif FIX == 1
        for( unsigned int j = 0; j < someBigNumber; j++ )
        {
            Array[ i ].value = Array[ i ].value + 2.;
        }
#endif
    }
	time1 = omp_get_wtime( );
    time = (time1 - time0);
    //printf("%f,", (double)((NUMBODIES*NUMBODIES*NUMSTEPS)/time)/1000000);
    printf("%f,", (4*someBigNumber/(double)time)/100000000);
}
