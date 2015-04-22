#include <stdlib.h>
#include <stdio.h>
#include <omp.h>

// Check if OpenMP is functional
#ifndef _OPENMP
fprintf( stderr, “OpenMP is not supported – sorry!\n” );
exit(1);
#endif

// Given definitions
#define XMIN     0.
#define XMAX     3.
#define YMIN     0.
#define YMAX     3.

#define Z00 0.
#define Z10 1.
#define Z20 0.
#define Z30 0.

#define Z01 1.
#define Z11 6.
#define Z21 1.
#define Z31 0.

#define Z02 0.
#define Z12 1.
#define Z22 0.
#define Z32 4.

#define Z03 3.
#define Z13 2.
#define Z23 3.
#define Z33 3.

// Number of Threads and Slices
#ifndef NUMS
#define NUMS 5
#endif
#ifndef NUMT
#define NUMT 4
#endif

// Magic carpet black box creator
double Height( unsigned long long iu, unsigned long long iv ) {   // iu,iv = 0 .. NUMS-1
    double u = (double)iu / (double)(NUMS-1);
    double v = (double)iv / (double)(NUMS-1);

    // the basis functions:

    double bu0 = (1.-u) * (1.-u) * (1.-u);
    double bu1 = 3. * u * (1.-u) * (1.-u);
    double bu2 = 3. * u * u * (1.-u);
    double bu3 = u * u * u;

    double bv0 = (1.-v) * (1.-v) * (1.-v);
    double bv1 = 3. * v * (1.-v) * (1.-v);
    double bv2 = 3. * v * v * (1.-v);
    double bv3 = v * v * v;

    // finally, we get to compute something:

    double height =    bu0 * ( bv0*Z00 + bv1*Z01 + bv2*Z02 + bv3*Z03 )
        + bu1 * ( bv0*Z10 + bv1*Z11 + bv2*Z12 + bv3*Z13 )
        + bu2 * ( bv0*Z20 + bv1*Z21 + bv2*Z22 + bv3*Z23 )
        + bu3 * ( bv0*Z30 + bv1*Z31 + bv2*Z32 + bv3*Z33 );

    return height;
}

// Display which version of OpenMP
void omp_version() {
    double ver;
    if (_OPENMP == 201307) {
        ver = 4.0;
    } else if (_OPENMP == 201107) {
        ver = 3.1;
    } else {
        ver = _OPENMP;
    }
    //printf("OpenMP version: %0.1f\n", ver);
}


int main( int argc, char *argv[ ] ) {
    omp_version();
    double myPartialSum = 0.0;
    double volume = 0.0;
    double norm;
    unsigned long long i;

    double start_time, time;

    //. . .

    // the area of a single full-sized tile:
    double fullTileArea = (  ( (XMAX-XMIN)/(double)(NUMS-1) )  *  ( ( YMAX - YMIN )/(double)(NUMS-1) )  );

    // sum up the weighted heights into the variable "volume"
    // using an OpenMP for loop and an addition reduction:
    omp_set_num_threads(NUMT);
    start_time = omp_get_wtime();
#pragma omp parallel for default(none), reduction(+:volume), private(myPartialSum,norm), shared(fullTileArea)
    for( i = 0; i < NUMS*NUMS; i++ )
    {
        unsigned long long iu = i % NUMS;  
        unsigned long long iv = i / NUMS;
        // Pass X and Y to Height
        myPartialSum = Height(iu, iv);

        norm = 1.0;
        // Fix volume for the corners and edges
        if (!(iu) || (iu == NUMS-1)) {
            norm = norm/2.0;
        }
        if (!(iv) || (iv == NUMS-1)) {
            norm = norm/2.0;
        }

        volume += (fullTileArea) * myPartialSum;
    }


    time = (omp_get_wtime() - start_time);

    //printf("%d,%d,%f,%f\n", NUMT, NUMS, time, volume);
#ifdef VOL
    printf("%f,", volume);
#else
    //printf("%f,", ((NUMS*NUMS)/time)/1000000);
    printf("%f,", time);
#endif
}
