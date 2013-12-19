/*********************************************************************
 *  ** Program Filename: pro_prime.c
 *   ** Author: Sam Quinn
 *    ** Date: 11/27/2013
 *     ** Description: Uses multiple processes to calculate the
 *     ** primes and happy numbers..
 *******************************************************************/
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <errno.h>
#include <signal.h>
#include <ctype.h>
#include <errno.h>
#include <fcntl.h>
#include <getopt.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <limits.h>
#include <semaphore.h>
#include <string.h>

#define _POSIX_C_SOURCE 200809L
#define _BSD_SOURCE

pid_t *procces;	//Process array
sem_t *sem;		//Semaphore
int num_pro = 100;	//Number of process default 100
unsigned long num;
unsigned char *map;	//Reference to the bitmap in shared memory
unsigned int *happy;	//Stores the number of happy numbers


typedef char word_t;
int BITS_PER_WORD = 8;
//returns the word where such number should be stored
#define WORD_OFFSET(b) ((b) / BITS_PER_WORD)
//Returns the bit to which such number should be stored
#define BIT_OFFSET(b)  ((b) % BITS_PER_WORD)
//Odd To Even Offset converts the number to the place where it is stored in the bitmap
#define OTEO(b)	((b + 1) / 2)

//Mounts and creates a shared memory object
void *mount_shmem(char *path, int object_size) {
	int shmem_fd;
	void *addr;

	shmem_fd = shm_open(path, O_CREAT | O_TRUNC | O_RDWR, S_IRUSR | S_IWUSR);
	if (shmem_fd == -1) {
		fprintf(stdout, "failed to open shared memory\n");
		exit(EXIT_FAILURE);
	}
	if (ftruncate(shmem_fd, object_size) == -1) {
		fprintf(stdout, "failed to resize shared memory\n");
		exit(EXIT_FAILURE);
	}

	addr = mmap(NULL, object_size, PROT_READ | PROT_WRITE, MAP_SHARED, shmem_fd,
			0);
	if (addr == MAP_FAILED) {
		fprintf(stdout, "failed to map shared memory\n");
		exit(EXIT_FAILURE);
	}

	return addr;
}

//Sets number as not prime
void clear_prime(int n) {
	//int *i;
	//sem_getvalue(&sem, i);
	//printf("SEMAPHORE == %d", i);
	if (sem_wait(sem) == -1) {
		fprintf(stdout, "Sem wait failed\n");
	} else {
		//printf("Recived sem\n");
	}
	map[WORD_OFFSET(n)] &= ~(1 << BIT_OFFSET(n));
	if (sem_post(sem) == -1) {
		fprintf(stdout, "Sem post failed\n");
	} else {
		//printf("Released sem\n");
	}

}

//Update the happy number
void set_happy() {
	if (sem_wait(sem) == -1) {
		fprintf(stdout, "Sem wait failed\n");
	} else {
		//printf("Recived sem\n");
	}
	//printf("IN HAPPY\n");
	++happy;
	//printf("HAPPY = %u\n", happy);
	if (sem_post(sem) == -1) {
		fprintf(stdout, "Sem post failed\n");
	} else {
		//printf("Released sem\n");
	}
}

//Returns if the number is prime or not
int get_prime(int n) {
	//pthread_mutex_lock(&mtex);
	word_t bit = map[WORD_OFFSET(n)] & (1 << BIT_OFFSET(n));
	//pthread_mutex_unlock(&mtex);
	return bit != 0;
}

//Waits for all of the children to finish
void burn_kids() {
	int i, status;
	for (i = 0; i < num_pro; ++i) {
		wait(NULL);
	}
}

//Sends signals to all of the offspring.
void handler(int action) {
	printf("\nENTERED HANDLER\n SIGNAL CAUGHT\n");
	int signal = 0;
	int i;

	switch (action) {
	case SIGQUIT:
		signal = SIGQUIT;
		break;
	case SIGHUP:
		signal = SIGQUIT;
		break;
	case SIGINT:
		signal = SIGINT;
		break;
	default:
		signal = SIGQUIT;
	}
	for (i = 0; i < num_pro; ++i) {
		kill(procces[i], signal);
	}

	//Kill all of the kids
	burn_kids();

	free(procces);

	sem_close(sem);

	if (shm_unlink("/quinnsa_shmem") == -1) {
		printf("Error deleting shared memory object");
		exit(EXIT_FAILURE);
	}

	exit(1);
}

//Scans through bitmap for next prime from the starting point received
// Returns next prime on success and 0 on failure.
unsigned long next_seed(unsigned int cur_seed) {
	//printf("CURSEED %u\n", cur_seed);
	unsigned long next;
	//	if(get_prime((cur_seed + 1) / 2) == 1){
	//		return cur_seed;
	//	}
	for (next = cur_seed + 2; next <= num; next += 2) {
		if (get_prime(OTEO(next)) != 0) {
			//printf("NEXT %u\n", next);
			return next;
		}
	}

	return 0;
}

//Sieve procces
static void *sieve(int arg) {

	unsigned long i, k, start, stop, t, v;
	int n = arg;

	start = ((n - 1) * (sqrt(num) / num_pro)) + 1;
	stop = (n * (sqrt(num) / num_pro)) + 1;

	//printf("N = %d BEGIN = %d, END = %d\n", n, start, stop);
	//printf("IN THREAD NUM = %u", num);
	i = start;
	if (i % 2 == 0) {
		--i;
	} else if (i < 3) {
		i = 3;
	}

	if (get_prime(OTEO(i)) != 1) {
		i = next_seed(i);
	} else if (i < start) {
		//printf("I is less than start\n");
		i = next_seed(i);
	}

	while (i != 0 && i < stop) {

		//printf("I = %u [%d]\n", i, n);

		for (k = i * i; k <= num; k += (2 * i)) {
			//printf("K = %u [%d]\n", k, n);
			clear_prime(OTEO(k));
		}
		i = next_seed(i);
	}

}

//Forks children to find all prime numbers
void fork_prime() {
	pid_t pid;
	int i;
	for (i = 1; i < num_pro; ++i) {
		switch (pid = fork()) {
		case 0:
			sieve(i);
			exit(EXIT_SUCCESS);
		case -1:
			break;
		default:
			//Waits for the specific PID of the suppressor process.
			procces[i] = pid;
			break;
		}
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

//Determines if a number is happy or not.
void check_mood(int arg, int verbose) {
	unsigned long old, start, stop, new;
	int i;
	int n = arg;
	start = ((n - 1) * (num / num_pro)) + 1;
	stop = (n * (num / num_pro)) + 1;

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
		old = next_seed(old);
	} else if (old < start) {
		old = next_seed(old);
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
		old = next_seed(old);
	}
}

//Forks children to run the check mood function
void fork_happy(int verbose) {
	pid_t pid;
	int i;
	for (i = 1; i < num_pro; ++i) {
		switch (pid = fork()) {
		case 0:
			check_mood(i, verbose);
			exit(EXIT_SUCCESS);
		case -1:
			break;
		default:
			//Waits for the specific PID of the suppressor process.
			procces[i] = pid;
			break;
		}
	}
}

//Seiral version of Sieve
void nonthread(unsigned long n) {
	unsigned long i, k, max;

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

//Counts the number of primes in the bitmap stored in shared memory
int count_primes(int verbose) {
	unsigned int prime_count = 1;
	unsigned long i, j, cur_word_offset;

	for (i = 0; i < ((num / 2) / BITS_PER_WORD) + 1; i++) {
		if (map[i] == 0) { //Skip empty words
			continue;
		}

		cur_word_offset = BITS_PER_WORD * i;

		for (j = 0; j < BITS_PER_WORD; ++j) {
			if (get_prime(cur_word_offset + j) == 1
					&& (((cur_word_offset + j) * 2) - 1) < num) {
				prime_count++;
				if(verbose == 1){
				printf("%u\n", (((cur_word_offset + j) * 2) - 1), get_prime(cur_word_offset + j));
				}
			}
		}
	}
	printf("YOUR PRIMES ARE %u\n", prime_count);
	return 0;
}

void p_usage(char* name) {
	fprintf(stderr, "Usage: %s [-]{nio} <archive> [file] \n"
			"		-n	 Number to find primes up too\n"
			"		-i	 Find primes up to INT_MAX\n"
			"		-u	 Find primes up to UINT_MAX\n"
			"		-v	 Verbose mode will print primes\n", name);
	exit(EXIT_FAILURE);
}

void init_map() {
	unsigned int i;
	/* Set words one at a time */
	for (i = 0; i < ((num / 2) / BITS_PER_WORD) + 1; i++) {
		map[i] = 0b11111111;
	}
	/* set 1 to not prime */
	clear_prime(1);
	happy = 0;
}

void initalize() {
	int i;
	procces = malloc(sizeof(pid_t) * num_pro);

	unsigned int map_size = (((num / 2) / BITS_PER_WORD) + 1);

	unsigned int object_size = 2 * map_size;

	void *addr = mount_shmem("/quinnsa_shmem", object_size);	//Creates the shared memory object

	sem = (sem_t*) addr; //map semaphore
	map = (unsigned char*) sem + sizeof(sem_t);	//Map bitmap after the semaphore
	happy = (unsigned int) map + map_size;	//Map the happy integer after the map and semaphore
	sem = sem_open("/quinnsa_sem", O_CREAT | O_EXCL, 0644, 1);	//Creates a semaphore with name
	sem_unlink("/quinnsa_sem");	//Unlinks the semaphore from the main function
	init_map();
}

int main(int argc, char **argv) {
	int kase, verbose = 0;
	unsigned int hap;
	time_t start, end;

	//Defines signal handler
	struct sigaction sig;

	sigemptyset(&sig.sa_mask);
	sig.sa_flags = 0;
	sig.sa_handler = handler;

	sigaction(SIGHUP, &sig, NULL);
	sigaction(SIGINT, &sig, NULL);
	sigaction(SIGQUIT, &sig, NULL);

	while ((kase = getopt(argc, argv, "n:p:iuv")) != -1)
		switch (kase) {

		case 'n':	//Defines the max number
			num = atoi(optarg);
			break;
		case 'p':	// Number of processes to use
			num_pro = atoi(optarg);
			break;
		case 'i':	// Max = sizeof INT_MAX
			num = INT_MAX;
			break;
		case 'u':	//Max = Sizeof UINT_MAX
			num = UINT_MAX;
			break;
		case 'v':	//Verbose print primes and happys
			verbose = 1;
			break;
		default:
			p_usage(argv[0]);

		}
	if (argc < 1) {
		p_usage(argv[0]); 	//If no argument are given print usage
	}

	//Initializes the bitmap, creates shared memory, creates semaphores and mounts shared memory
	initalize();

	nonthread(num);
	time(&start);
	fork_prime();	//Forks children for the Sieve Function
	time(&end);

	printf("Calculated %u primes in %.2f seconds\nCounting the primes now.\n",
			num, difftime(end, start));

	time(&start);
	count_primes(verbose);	//Counts the primes in the bitmap
	time(&end);

	printf("and it took %.2f seconds to count.\nDetermining their mood now..\n",
			difftime(end, start));

	fork_happy(verbose);	//Forks children for finding happy numbers

	printf("There are %u happy numbers, and it took %.2f seconds to determine their mood.\n",
			&happy, difftime(end, start));

	burn_kids();	//Waits on all of the children

	sem_close(&sem);	//Deletes the semaphore

	//Deletes the shared memory object
	if (shm_unlink("/quinnsa_shmem") == -1) {
		printf("Error deleting shared memory object");
		exit(EXIT_FAILURE);
	}

	free(procces); //Free proccess array

	return 0;
}

