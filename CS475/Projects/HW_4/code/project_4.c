#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>
#include <time.h>



#ifndef NUMT
#define NUMT           4
#endif
#ifndef NUM
#define NUM            4
#endif

#define ENDSIM          2020
#define MATH_E          2.71828

int     NowYear;        // 2015 - 2020
int     NowMonth;       // 0 - 11

float   NowPrecip;      // inches of rain per month
float   NowTemp;        // temperature this month
float   NowHeight;      // grain height in inches
int     NowNumDeer;     // number of deer in the current population
int     Fire;           // forest fire

const float GRAIN_GROWS_PER_MONTH =     8.0;
const float ONE_DEER_EATS_PER_MONTH =   0.5;

const float AVG_PRECIP_PER_MONTH =      6.0;
const float AMP_PRECIP_PER_MONTH =      6.0;
const float RANDOM_PRECIP =             2.0;

const float AVG_TEMP =                  50.0;
const float AMP_TEMP =                  20.0;
const float RANDOM_TEMP =               10.0;

const float MIDTEMP =                   40.0;
const float MIDPRECIP =                 10.0;

float Ranf(float LO, float HI) {
    return LO + (float) (rand()) /( (float) (RAND_MAX/(HI-LO)));
}

float ang() {
    return (  30.*(float)NowMonth + 15.  ) * ( M_PI / 180. );
}

float getTemp() {
    float temp = AVG_TEMP - AMP_TEMP * cos( ang() );
    return temp + Ranf( -RANDOM_TEMP, RANDOM_TEMP );
}


float getPrecip() {
    float precip = AVG_PRECIP_PER_MONTH + AMP_PRECIP_PER_MONTH * sin( ang() );
    precip += Ranf( -RANDOM_PRECIP, RANDOM_PRECIP );
    if( precip < 0. ) {
        return 0.;
    }
    return precip;
}



void GrainDeer() {
    int die, reproduce;
    while (NowYear <= ENDSIM) {
        // Reset varibles
        die = 0;
        reproduce = 0;

        // compute a temporary next-value
        if (Fire) {
            // Deer die
            die = NowNumDeer - (rand() % NowNumDeer - 1);
        }
        if (NowNumDeer > NowHeight) {
            // Deer Die
            die++;
        } else if (NowNumDeer < NowHeight) {
            // Deer reproduce
            reproduce++;
        }
        // DoneComputing barrier:
        #pragma omp barrier
        
        NowNumDeer += reproduce;
        NowNumDeer -= die;
        if (NowNumDeer <= 0) {
            NowNumDeer = 1;
        }
        // DoneAssigning barrier:
        #pragma omp barrier
        
        // DonePrinting barrier:
        #pragma omp barrier
    }
}

void Grain() {
    float temp, precip, tempFactor, precipFactor,burn;

    while (NowYear <= ENDSIM) { 
        // compute a temporary next-value
        burn = 0;
        temp      = NowTemp;
        precip    = NowPrecip;
        tempFactor    = pow(MATH_E, - pow(((temp - MIDTEMP)/10), 2));
        precipFactor  = pow(MATH_E, - pow(((precip - MIDPRECIP)/10), 2));

        //printf("Pfact:%f\tTtemp:%f\n",tempFactor, precipFactor);    

        if (Fire) {
            // Grain burns
            burn = NowHeight - Ranf(0., NowHeight - 1);
        }
        // DoneComputing barrier:
        #pragma omp barrier

        NowHeight += tempFactor * precipFactor * GRAIN_GROWS_PER_MONTH;
        NowHeight -= ((float)NowNumDeer * ONE_DEER_EATS_PER_MONTH) + burn;

        if (NowHeight < 0) {
            NowHeight = .2;
        } else if (NowHeight > 100) {
            NowHeight = 40;
        }
        // DoneAssigning barrier:
        #pragma omp barrier
        
        // DonePrinting barrier:
        #pragma omp barrier
    }
}

void Forestfire() {
    int tempFire;   
    while (NowYear <= ENDSIM) { 
        if (getTemp() > AVG_TEMP && getPrecip() < AVG_PRECIP_PER_MONTH) {
            // Forest Fire starts
            tempFire = 1;
            //printf("Fire!!!!!!!!!!!!!!!!!!!\n");
        } else {
            tempFire = 0;
        }
        // DoneComputing barrier:
        #pragma omp barrier

        Fire = tempFire;
        // DoneAssigning barrier:
        #pragma omp barrier

        // DonePrinting barrier:
        #pragma omp barrier
    }
}

void Watcher() {
    int newYear, newMonth, newTemp, newPrecip;
    while (NowYear <= ENDSIM) { 
        newMonth = NowMonth + 1;
        if (newMonth > 11) {
            newMonth = 0;
            newYear = NowYear + 1;
        } else {
            newYear = NowYear;
        }
        newTemp = getTemp();
        newPrecip = getPrecip();
        // DoneComputing barrier:
        #pragma omp barrier

        NowYear = newYear;
        NowMonth = newMonth;
        NowTemp = newTemp;
        NowPrecip = newPrecip;
        // DoneAssigning barrier:
        #pragma omp barrier

        printf("%d-%d,%f,%f,%d,%f,%d\n", NowMonth + 1, NowYear, NowTemp, NowPrecip, NowNumDeer, NowHeight, Fire);
        // DonePrinting barrier:
        #pragma omp barrier
    }
}

int main() {
    // starting date and time:
    NowMonth =    0;
    NowYear  = 2015;
    /* initialize random seed: */
    srand (time(NULL));

    // starting state (feel free to change this if you want):
    NowNumDeer = 1;
    NowHeight =  1.;
    Fire = 0;
    omp_set_num_threads( 4 );
    #pragma omp parallel sections
    {
        #pragma omp section
        {
            GrainDeer();
        }

        #pragma omp section
        {
            Grain();
        }

        #pragma omp section
        {
            Forestfire();
        }

        #pragma omp section
        {
            printf("Date,Temp,Precip,Deer,Grain,Fire\n");
            Watcher();
        }
    }       // implied barrier -- all functions must return to get past here
    return 0;
}
