/*********************************************************************
 *  ** Program Filename: thr_prime.c
 *   ** Author: Sam Quinn
 *    ** Date: 11/27/2013
 *     ** Description: Uses multiple threads to calculate primes and
 *     ** happy numbers.
 ********************************************************************/
#include <stdio.h>
#include <limits.h>
#include <getopt.h>
#include <math.h>
#include <pthread.h>
#include <sys/times.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <signal.h>

#define _POSIX_C_SOURCE 200809L
#define _BSD_SOURCE

//pthread_t thr[32];
pthread_mutex_t mtex[20];	//Stores all of muy mutexes
int set_mutex = 1;	//Weather to uses mutexes or not default is 1
int verbose = 0;	//Weather to print in verbose mode or not default 0
int threads = 32;	//Number of threads default is 32
long num;	//Stores the max number
unsigned int happy;	//Stores how many happy numbers there are
unsigned char *map;	//Stores the bitmap

typedef char word_t;

int BITS_PER_WORD = 8;
//returns the word where such number should be stored
#define WORD_OFFSET(b) ((b) / BITS_PER_WORD)
//Returns the bit to which such number should be stored
#define BIT_OFFSET(b)  ((b) % BITS_PER_WORD)
//Odd To Even Offset converts the number to the place where it is stored in the bitmap
#define OTEO(b)	((b + 1) / 2)

//void burn_kids() {
//	int i, status;
//	for (i = 1; i < threads; i++) {
//		pthread_join(thr[i], NULL);
//	}
//}

//void handler(int action) {
//	printf("\nENTERED HANDLER\n SIGNAL CAUGHT\n");
//	int signal = 0;
//	int i;
//
//	switch (action) {
//	case SIGQUIT:
//		signal = SIGQUIT;
//		break;
//	case SIGHUP:
//		signal = SIGQUIT;
//		break;
//	case SIGINT:
//		signal = SIGINT;
//		break;
//	default:
//		signal = SIGQUIT;
//	}
//	for (i = 0; i < threads; ++i) {
//		pthread_kill(thr[i], signal);
//	}
//
//	//Kill all of the kids
//	burn_kids();
//
//	free(thr);
//
//	exit(1);
//}

//Returns a number for the mutex
int lock(unsigned int n) {
	int lock;
	unsigned int k = (num / 20);
	/*******Debug********/
	//printf("N = %u", n);
	/********************/
	if (n < k) {
		return 1;
	} else if (n > k && n < (2 * k)) {
		return 2;
	} else if (n > (2 * k) && n < (3 * k)) {
		return 3;
	} else if (n > (3 * k) && n < (4 * k)) {
		return 4;
	} else if (n > (4 * k) && n < (5 * k)) {
		return 5;
	} else if (n > (5 * k) && n < (6 * k)) {
		return 6;
	} else if (n > (6 * k) && n < (7 * k)) {
		return 7;
	} else if (n > (7 * k) && n < (8 * k)) {
		return 8;
	} else if (n > (8 * k) && n < (9 * k)) {
		return 9;
	} else if (n > (9 * k) && n < (10 * k)) {
		return 10;
	} else if (n > (10 * k) && n < (11 * k)) {
		return 11;
	} else if (n > (11 * k) && n < (12 * k)) {
		return 12;
	} else if (n > (12 * k) && n < (13 * k)) {
		return 13;
	} else if (n > (13 * k) && n < (14 * k)) {
		return 14;
	} else if (n > (14 * k) && n < (15 * k)) {
		return 15;
	} else if (n > (15 * k) && n < (16 * k)) {
		return 16;
	} else if (n > (16 * k) && n < (17 * k)) {
		return 17;
	} else if (n > (17 * k) && n < (18 * k)) {
		return 18;
	} else if (n > (18 * k) && n < (19 * k)) {
		return 19;
	} else if (n > (19 * k) && n <= num) {
		return 20;
	} else {
		return 1;
	}
}

//Sets number as not prime
void clear_prime(unsigned int n) {
	if (set_mutex == 1) {
		int nlock = lock((n * 2) - 1);	//Gets section mutex
		pthread_mutex_lock(&mtex[nlock]);
		map[WORD_OFFSET(n)] &= ~(1 << BIT_OFFSET(n));
		pthread_mutex_unlock(&mtex[nlock]);
	} else {
		map[WORD_OFFSET(n)] &= ~(1 << BIT_OFFSET(n));
	}
}

//Update the happy number
void set_happy() {
	pthread_mutex_lock(&mtex[1]);
	++happy;
	pthread_mutex_unlock(&mtex[1]);
}

//Returns if the number is prime or not
int get_prime(unsigned int n) {
	//pthread_mutex_lock(&mtex);
	word_t bit = map[WORD_OFFSET(n)] & (1 << BIT_OFFSET(n));
	//pthread_mutex_unlock(&mtex);
	return bit != 0;
}

//Counts the number of primes in the bitmap
void count_primes() {
	unsigned int prime_count = 1;
	unsigned long i, j, cur_word_offset;
	if (verbose == 1) {
		printf("2\n");	//Prints 2 since the bitmap is not initailzed to hold 2
	}

	for (i = 0; i < ((num / 2) / BITS_PER_WORD) + 1; i++) {
		if (map[i] != 0) {
			cur_word_offset = BITS_PER_WORD * i;
			for (j = 0; j < BITS_PER_WORD; ++j) {
				if (get_prime(cur_word_offset + j) == 1
						&& (((cur_word_offset + j) * 2) - 1) < num) {
					prime_count++;
					if (verbose == 1) {
						printf("%u\n", (((cur_word_offset + j) * 2) - 1));
					}
				}
			}
		}
	}
	printf("There are %u primes, ", prime_count);
}

//Initializes The bitmap without evens
void init_map() {
	unsigned int i;
	//Initialize map with all primes since we are skipping evens
	for (i = 0; i < ((num / 2) / BITS_PER_WORD) + 1; i++) {
		map[i] = 0b11111111;
	}
	// set 1 as not prime
	clear_prime(1);
	happy = 0;
}

//Scans through bitmap for next prime from the starting point received
// Returns next prime on success and 0 on failure.
unsigned long next_prime(unsigned int prime) {
	/************Debug****************/
	//printf("CURSEED %u\n", cur_seed);
	/*********************************/
	unsigned long next;
	for (next = prime + 2; next <= num; next += 2) {//Scans for prime from starting number
		if (get_prime(OTEO(next)) != 0) {
			/**********Debug************/
			//printf("NEXT %u\n", next);
			/***************************/
			return next;
		}
	}

	return 0;
}

void p_usage(char* exe) {
	fprintf(stderr, "Usage: %s [-]{niutmv}\n"
			"		-n	 Number to find primes up too\n"
			"		-i	 Find primes up to INT_MAX\n"
			"		-u	 Find primes up to UINT_MAX\n"
			"		-t	 The number of threads to use\n"
			"		-m 	 Weather to use mutexes or not\n"
			"		-v 	 Print primes and happy numbers\n", exe);
	exit(EXIT_FAILURE);
}

//Sieve proccess
static void *sieve(void *arg) {

	unsigned long i, k, start, stop, t, v;
	int n = (int) arg;

	start = ((n - 1) * (sqrt(num) / threads)) + 1;//Calculate the start number for this specific thread
	stop = (n * (sqrt(num) / threads)) + 1;	//Calculate the Stop number for this specific thread

	/******************-Debugging-prints**********************/
	//printf("N = %d BEGIN = %d, END = %d\n", n, start, stop);
	//printf("IN THREAD NUM = %u", num);
	/*********************************************************/

	i = start;
	if (i % 2 == 0) {
		--i;
	} else if (i < 3) {
		i = 3;	//If the number is less then 3 set the number to 3
	}

	if (get_prime(OTEO(i)) != 1) {
		i = next_prime(i);//If the number is not prime get the next prime number
	} else if (i < start) {
		i = next_prime(i);//If the number is less than the designated start then find next prime
	}

	while (i != 0 && i < stop) {

		/**********Debug****************/
		//printf("I = %u [%d]\n", i, n);
		/*******************************/

		for (k = i * i; k <= num; k += (2 * i)) {
			clear_prime(OTEO(k));	//Clear all multiples of the number i
		}
		i = next_prime(i);		//Gets the next prime from the bitmap
	}
}

// Referenced http://forums.devshed.com/c-programming-42/finding-happy-primes-in-c-661361.html for this function.
unsigned long sum_square(unsigned long num) {
	unsigned long digit = 0, add = 0, new = 0;

	/***********-Debug************/
	//printf("SQUARE = %u\n", num);
	/*****************************/

	do {
		digit = num % 10;
		add = digit * digit;
		new = new + add;
		num = (num - digit) / 10;
	} while (num > 0);
	return new;
}

//Checks if a number is happy or not
void check_mood(void *arg) {
	unsigned long old, start, stop, new;
	int i;
	int n = (int) arg;
	start = ((n - 1) * (num / threads)) + 1;
	stop = (n * (num / threads)) + 1;

	/******************-Debugging-prints**********************/
	//printf("N = %d BEGIN = %d, END = %d\n", n, start, stop);
	//printf("IN THREAD NUM = %u", num);
	/*********************************************************/

	old = start;
	if (old % 2 == 0) {
		--old;
	} else if (old < 3) {
		old = 3;
	}

	if (get_prime(OTEO(old)) != 1) {
		old = next_prime(old);
	} else if (old < start) {
		old = next_prime(old);
	}

	while (old != 0 && old < stop) {
		new = old;
		for (i = 1; (i < 810); i++) {
			new = sum_square(new);
			if (new == 1) {
				set_happy();
				if (verbose == 1) {
					printf("%u\n", old);
				}
				break;
			} else if (new == 4 || new == old) {
				break;
			}
		}
		old = next_prime(old);
	}
}

//Seiral version of Sieve
void nonthread(int n) {
	unsigned int i, k, max;

	max = sqrt(n);

	for (i = 3; i <= sqrt(max); i++) {
		if (i >= 3 && i % 2 != 0) {
			for (k = i * i; k <= max; k += i) {
				if (k % 2 != 0) {
					if (get_prime(OTEO(k)) == 1) {
						clear_prime(OTEO(k));
					}
				}
			}
		}
	}
}
void spawn_threads(int program) {
	pthread_t thread[threads];
	//void *res;
	int s, i;

	pthread_attr_t attr;

	pthread_attr_init(&attr);
	if (program == 1) {
		for (i = 1; i <= threads; i++) {
			s = pthread_create(&thread[i], &attr, sieve, (void*) (i));
			if (s != 0) {
				perror("pthread_create");
			}
		}

		//printf("Message from Main()\n");
		//thr = threads;
		//printf("Message from Main()\n");
		for (i = 1; i < threads; i++) {
			pthread_join(thread[i], NULL);
			if (s != 0) {
				perror("pthread_join");
			}
			//printf("Thread returned %ld\n", (long) res);
		}
	} else if (program == 2) {
		for (i = 1; i <= threads; i++) {
			s = pthread_create(&thread[i], &attr, check_mood, (void*) (i));
			if (s != 0) {
				perror("pthread_create");
			}
		}

		//printf("Message from Main()\n");
		for (i = 1; i < threads; i++) {
			pthread_join(thread[i], NULL);
			if (s != 0) {
				perror("pthread_join");
			}
			//printf("Thread returned %ld\n", (long) res);
		}
	}
}

int main(int argc, char **argv) {
	int kase, i;
	time_t start, end;

//	struct sigaction sig;
//
//	sigemptyset(&sig.sa_mask);
//	sig.sa_flags = 0;
//	sig.sa_handler = handler;
//
//	sigaction(SIGHUP, &sig, NULL);
//	sigaction(SIGINT, &sig, NULL);
//	sigaction(SIGQUIT, &sig, NULL);

	while ((kase = getopt(argc, argv, "n:t:iumv")) != -1)
		switch (kase) {

		case 'n':	//User defined max
			num = atoi(optarg);
			break;
		case 't':	//Number of threads to use
			threads = atoi(optarg);
			break;
		case 'i':	//Max = size of signed int
			num = INT_MAX;
			break;
		case 'u':	//Max = size of unsigned int
			num = UINT_MAX;
			break;
		case 'm':	//Do not use mutexes
			set_mutex = 0;
			break;
		case 'v':	//Verbose print primes and happys
			verbose = 1;
			break;
		default: 	// The ? case print usage
			p_usage(argv[0]);

		}
	if (argc < 2) {
		p_usage(argv[0]);
	}

	unsigned int map_size = (((num / 2) / BITS_PER_WORD) + 1);
	map = malloc(map_size * BITS_PER_WORD);

	for (i = 1; i <= 20; ++i) {
		pthread_mutex_init(&mtex[i], NULL);
	}

	init_map();		//Initialize map

	printf(
			"Finding primes.\nRunning a serial version of Sieve up to sqrt(sqrt(%u))"
					" to expedite the parallel version of Sieve..\n", num);

	nonthread(num);	//Run Non threaded version of Sieve up to sqrt(sqrt(max))

	printf("Starting parallel version now..\n");
	time(&start);	//Start time
	spawn_threads(1);	// Spawn Sieve threads
	time(&end);		//End time

	printf("Calculated %u primes in %.2f seconds\nCounting the primes now.\n",
			num, difftime(end, start));

	time(&start);	//Start time
	count_primes(verbose);	//Count primes from bitmap
	time(&end);	//End time
	printf("and it took %.2f seconds to count.\nDetermining their mood now..\n",
			difftime(end, start));

	time(&start);	//Start time
	spawn_threads(2);	//Spawn Threads for happy numbers
	time(&end);		//End time
	printf(
			"There are %u happy Primes and it took %.2f seconds to determine their mood.\n",
			happy, difftime(end, start));
	free(map);

	return 0;
}
