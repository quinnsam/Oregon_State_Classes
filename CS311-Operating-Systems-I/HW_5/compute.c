/*********************************************************************
 *  ** Program Filename: compute.c
 *   ** Author: Sam Quinn
 *    ** Date: 12/8/2013
 *     ** Description: compute's job is to compute perfect numbers.
 *     		It tests all numbers beginning from its
 *     		starting point, subject to the constraints
 *    		below. There may be more than one copy of
 *     		compute running simultaneously.
 *******************************************************************/

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/socket.h>
#include <resolv.h>
#include <time.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <regex.h>


#define PORT 			24400			// My port
#define SERVER_ADDR     "127.0.0.1"     // localhost
#define MAXBUF          1024			//Max socket size

int num_pro = 1;	//Number of processes to fork
long limit = 0;		//The limit of what number to check up to for perfect numbers.

pid_t *procces;	//Process array

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

	exit(1);
}

//Sends handshakes to the server
int meet_friends(int main, int sockfd) {
	char buffer[MAXBUF];
	if (main == 1) {
		write(sockfd, "<message type=\"handshake\" from=\"compute\"></message>",
				51);
	} else if (main == 0) {
		write(sockfd, "<message type=\"handshake\" from=\"commain\"></message>",
				51);
	}

	bzero(buffer, MAXBUF);
	recv(sockfd, buffer, sizeof(buffer), 0);
	//printf("%s\n", buffer);
	if (strcmp(buffer, "<message type=\"handshake\" from=\"manage\"></message>")
			== 0) {
		if (main == 1) {
			printf("Compute and Manage have become friends\n");
		} else if (main == 0) {
			printf("Commain and Manage have become friends\n");
		}

	}

	return 1;
}

//Calculates how many modulo proccesses run in 15 seconds
long benchmark() {
	int bench, j;
	unsigned long i;
	volatile unsigned long b = 0;
	clock_t start, stop;
	start = clock();
	j = 17;
	i = 0;
	stop = start; //Just to get rid of the used before declared warning

	//Loops until it has been 15 seconds
	while (((int) (stop - start) / CLOCKS_PER_SEC) < 15) {
		b += i % j;
		++i;
		stop = clock();
	}
	int time_elapsed = (int) (stop - start) / CLOCKS_PER_SEC;

	printf("Done.\nIt took 15 seconds to calculate %lu  modulo operations.\n", i);

	return i;	//returns the number of mod operations from 15 seconds.
}

//This function is ran by the offspring of main.
void compute() {
	int sockfd;
	long i;
	long old = 2;
	struct sockaddr_in dest;
	char buffer[MAXBUF];
	regex_t regex;

	//Opens socket for streaming
	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		perror("Socket");
		exit(errno);
	}

	//Initializes server address/port struct
	bzero(&dest, sizeof(dest));
	dest.sin_family = AF_INET;
	dest.sin_port = htons(PORT);
	if (inet_aton(SERVER_ADDR, &dest.sin_addr.s_addr) == 0) {
		perror(SERVER_ADDR);
		exit(errno);
	}

	//Connects to server
	if (connect(sockfd, (struct sockaddr*) &dest, sizeof(dest)) != 0) {
		perror("Connect ");
		exit(errno);
	}

	//Sends and recieves handshake from server.
	meet_friends(1, sockfd);

	while (1) {

		printf("Benchmarking...");
		fflush(stdout);
		snprintf(buffer, MAXBUF,
				"<message type=\"new_limit\" from=\"compute\" value=\"%ld\" old=\"%ld\"></message>",
				benchmark(), limit);

		write(sockfd, buffer, strlen(buffer));	//Asks for a new limit

		bzero(buffer, MAXBUF);
		recv(sockfd, buffer, sizeof(buffer), 0);
		//printf("%s\n", buffer);
		old = limit;
		limit = atol(buffer);

		printf("Finding perfects from %ld to %ld\n", old, limit);
		fflush(stdout);
		for (i = old; i < limit; ++i) {
			//printf("%ld\n",i);
			if (check_perfect(i) != -1) {	//Sends message only if it is a perfect number.
				snprintf(buffer, MAXBUF,
						"<message type=\"perfect\" from=\"compute\" value=\"%ld\"></message>",
						i);
				printf("(%ld) is perfect, sending it over.\n", i);
				fflush(stdout);
				write(sockfd, buffer, strlen(buffer));
			}
		}


	}
}

//Forks children to find all prime numbers
void fork_compute() {
	procces = malloc(sizeof(pid_t) * num_pro);
	pid_t pid;
	int i;
	for (i = 1; i <= num_pro; ++i) {
		switch (pid = fork()) {
		case 0:
			compute();
			exit(EXIT_SUCCESS);
		case -1:
			break;
		default:
			//Adds the PID of the compute process to the process list.
			procces[i] = pid;
			break;
		}
	}
}

int main() {
	int sockfd;		//Socket file descriptor
	struct sockaddr_in dest;	//struct containing address and port.
	char buffer[MAXBUF];		//Buffer for read and write opperations.

	struct sigaction sig;		//Signal handling struct

	sigemptyset(&sig.sa_mask);
	sig.sa_flags = 0;
	sig.sa_handler = handler;	//Tells the system to use my signal handler

	sigaction(SIGHUP, &sig, NULL);
	sigaction(SIGINT, &sig, NULL);
	sigaction(SIGQUIT, &sig, NULL);

	//Opens socket for streaming
	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		perror("Socket");
		exit(errno);
	}

	//Initializes server address/port struct
	bzero(&dest, sizeof(dest));
	dest.sin_family = AF_INET;
	dest.sin_port = htons(PORT);
	if (inet_aton(SERVER_ADDR, &dest.sin_addr.s_addr) == 0) {
		perror(SERVER_ADDR);
		exit(errno);
	}

	//Connects to server
	if (connect(sockfd, (struct sockaddr*) &dest, sizeof(dest)) != 0) {
		perror("Connect encountered a problem");
		exit(EXIT_FAILURE);
	}

	meet_friends(0, sockfd);	//Sends and receives handshake from server

	fork_compute();	//Fork off compute process

	//Wait for termination key from server.
	bzero(buffer, MAXBUF);
	recv(sockfd, buffer, sizeof(buffer), 0);
	printf("%s\n", buffer);
	if (strcmp(buffer, "<message type=\"die\" from=\"manage\"></message>")
			== 0) {
		printf("Getting killed, Run!\n");
		handler(SIGQUIT);
	}

	/*---Clean up---*/
	close(sockfd);
	return 0;
}

//Checks if a number is perfect or not
int check_perfect(int num) {
	int sum[num / 2];
	int i, half, perfect;
	half = (num / 2);
	perfect = 0;

	for (i = 0; i < half; ++i) {
		sum[i] = 0;
	}

	for (i = 1; i <= half; ++i) {
		if ((num % i) == 0) {
			sum[i - 1] = i;
		}
	}

	for (i = 0; i < half; ++i) {
		perfect += sum[i];
	}

	if (perfect == num) {
		return perfect;
	} else {
		return -1;
	}
}
