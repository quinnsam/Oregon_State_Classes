/*********************************************************************
 *  ** Program Filename: myar.c
 *   ** Author: Sam Quinn
 *    ** Date: 10/30/2013
 *     ** Description: Creates mutilple sorting process.
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

//Max word length
#define MAX_LENGTH 100

pid_t *procces;
int num_pro = 1;
int **sorter;
int **supper;

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

//Finds the lowest alphabetical word in the array and returns its index
int position(char **words) {
	int index = -1;
	int i;
	int eofs = 0;

	//Finds the first word in the array that is not NULL
	for (i = 0; i < num_pro; ++i) {
		if (words[i] != NULL) {
			index = i;
			break;
		}
	}

	//If index is still -1 then the whole array is full of NULLs
	if (index == -1) {
		return index;
	}

	//Set index to the lowest alphabetical word in the array
	for (i = 0; i < num_pro; ++i) {
		if (words[i] != NULL) {
			if (strcmp(words[i], words[index]) < 0) {
				index = i;
			}
		}

	}
	return index;
}

void suppressor(char*file, int flag) {
	int i;
	int first = 1;
	int k = 0;
	char **save;
	char *print;
	FILE *in_st[num_pro];
	int pos, fd;
	int eofs = 0;

	//printf("SUPPRESOR FILE(%s) FLAG(%d)\n", file, flag);

	//If an output file is given it either creates it here or appends the old one.
	if (flag == 1) {
		fd = open(file, O_WRONLY | O_APPEND | O_CREAT, 0666);
		if (fd == -1) {
			printf("There was an error opening/creating FILE(%s)\n", file);
		}
	}
	//Allocates memory
	save = malloc(num_pro * sizeof(char *));
	print = malloc(MAX_LENGTH * sizeof(char));

	for (i = 0; i < num_pro; ++i) {
		save[i] = malloc(MAX_LENGTH * sizeof(char));
	}

	//Sets in_st with the stream from the out pipes.
	for (i = 0; i < num_pro; ++i) {
		in_st[i] = fdopen(supper[i][0], "r");
		//Gets the first word from all of the pipes.
		if (fgets(save[i], MAX_LENGTH, in_st[i]) == NULL) {
			save[i] = NULL;
			eofs++;
		}
	}

	//Uses strcmp to see which word is lowest in alphabetical order.
	pos = position(save);

	while (eofs < num_pro) {

		//Runs this section of the code only on the first run.
		if (first == 1) {
			first = 0;
			if (flag == 0) {
				printf("\nYour Sorted words are\n\n");
				//Prints first word
				printf("%s", save[pos]);
			} else {
				write(fd, "\nYour Sorted words are\n\n", 24);
				//Writes first word
				write(fd, (" %s \n", save[pos]), strlen(save[pos]));
			}
		}

		//Gets another word from pipes.
		if (fgets(save[pos], MAX_LENGTH, in_st[pos]) == NULL) {
			save[pos] = NULL;
			eofs++;
		}

		pos = position(save);

		//Prints last word.
		if (eofs == num_pro) {
			if (flag == 0) {
				printf("%s", print);
			} else {
				write(fd, (" %s \n", print), strlen(print));
			}
		}
		//Every pipe is done handing out words.
		if (pos == -1) {
			//printf("ENTIRE ARRAY IS NULL\n");
			break;
		}

		//Checks if it is a duplicate if not prints.
		if (strcmp(print, save[pos]) != 0) {

			if (flag == 0) {

				printf("%s", print);
			} else {

				write(fd, (" %s\n", print), strlen(print));

			}
		}

		//Copys lowest word into print to be printed
		strncpy(print, save[pos], MAX_LENGTH);

	}

	//Frees memory and closes streams
	for (i = 0; i < num_pro; ++i) {
		free(save[i]);
	}
	free(save);

	for (i = 0; i < num_pro; ++i) {
		fclose(in_st[i]);
	}
}

//Forks another process that the suppressor will live in.
void fork_sup(char* file, int flag) {
	pid_t pid;
	switch (pid = fork()) {
	case 0:
		suppressor(file, flag);
		break;
	case -1:
		break;
	default:
		//Waits for the specific PID of the suppressor process.
		waitpid(pid, NULL, 0);
		break;
	}
}

void parser(char* file, int flag) {
	int mod = 0;
	int i, fd;
	int scan = 1;
	char buf[MAX_LENGTH];
	FILE *out[num_pro];
	FILE *input;

	//printf("PARSER FILE(%s) FLAG(%d)\n", file, flag);

	//If a input file is entered it opens it here.
	if (flag == 1) {

		fd = open(file, O_RDONLY);
		input = fdopen(fd, "r");
	}

	//Sets out array to the file descriptors from the in pipes.
	for (i = 0; i < num_pro; ++i) {
		out[i] = fdopen(sorter[i][1], "w");
	}

	//Gets rid of errors that occur with words leading with non
	//Alphabetical characters.
	if (flag == 1) {
		//Scan all of the good stuff we want from the input file.
		scan = fscanf(input, "%*[^a-zA-Z]");
	} else {
		//Scan all of the good stuff we want from STDIN.
		scan = scanf("%*[^a-zA-Z]");
	}

	//Loop till the end of the file.
	while (scan != EOF) {
		if (flag == 1) {
			//Scan all of the good stuff we want from the input file.
			scan = fscanf(input, "%[a-zA-Z]", buf);
		} else {
			//Scan all of the good stuff we want from STDIN.
			scan = scanf("%[a-zA-Z]", buf);
		}
		//If buffer is not empty change input to lowercase.
		if (buf[0] != '\0') {
			for (i = 0; i < sizeof(buf); ++i) {
				buf[i] = tolower(buf[i]);
			}
			//Sends buffer through pipe
			fputs(buf, out[mod % num_pro]);
			//Sends the end of line character through the same pipe
			fputs("\n", out[mod % num_pro]);

		}
		//Resets the buffer
		buf[0] = '\0';

		//Checks if we are reading in from STDIN or a File.
		if (flag == 1) {
			//Scan leaving out all of the stuff we don't want.
			scan = fscanf(input, "%*[^a-zA-Z]");
		} else {
			//Scan leaving out all of the stuff we don't want.
			scan = scanf("%*[^a-zA-Z]");
		}
		//Increment the value that the number of processes is modulus by.
		++mod;
	}

	//closes all streams we made.
	for (i = 0; i < num_pro; ++i) {
		fclose(out[i]);
	}

}

void sort_func() {
	pid_t p;
	int i;

	//Creates pipe file descriptors 2 for each pipe.
	for (i = 0; i < num_pro; ++i) {
		if (pipe(sorter[i]) == -1 || pipe(supper[i]) == -1) {
			printf(
					"Something went wrong with the pipes, Better call a plumber!\n");
			exit(-1);
		}

		switch (p = fork()) {
		case 0:
			//printf("I am the child, and my PID is %d, (%d)\n", getpid(),
			//		getppid());

			//Closes both the STDIN and STDOUT becasue we need to dup
			// Our pipes to them.
			close(STDIN_FILENO);
			close(STDOUT_FILENO);

			//Checks if in pipes are already are duped to STDIN if not
			//Then sets the read end of the pipes to STDIN
			if (sorter[i][0] != STDIN_FILENO) {
				if (dup2(sorter[i][0], STDIN_FILENO) != STDIN_FILENO) {
					printf("something went wrong in dup STDIN_FILENO. \n");
					exit(-1);
				}
			}
			//close the read end of the output pipes since they only need to write
			close(supper[i][0]);

			//Checks if out pipes are already are duped to STDOUT if not
			//Then sets the write end of the pipes to STDOUT
			if (supper[i][1] != STDOUT_FILENO) {
				if (dup2(supper[i][1], STDOUT_FILENO) != STDOUT_FILENO) {
					printf("something went wrong in dup STDOUT_FILENO. \n");
					exit(-1);
				}
			}

			//Since we have duped all of the pipes we need to close all of the
			// ones we are not using anymore.
			close(sorter[i][0]);
			close(sorter[i][1]);
			close(supper[i][0]);
			close(supper[i][1]);

			execlp("sort", "sort", (char *) NULL);
			_exit(127);		//This will only run if exec() fails.
			break;

		case -1:
			//this is the OOPS case.
			perror("Could not create Child");
			exit(-1);
			break;

		default:
			//printf("I am the parent, and my PID is %d\n", getpid());

			//Saves the PID in the global process array.
			procces[i] = p;

			//Closes all of the in pipes
			if (close(sorter[i][0]) == -1) {
				printf("An error occured closing the pipes, I=%d..Sorter \n",
						i);
				exit(-1);
			}

			//Closes all of the out pipes
			if (close(supper[i][1]) == -1) {
				printf("An error occured closing the pipes, I=%d..Supper \n",
						i);
				exit(-1);
			}
			break;

		}

	}
}

void p_usage(char* name) {
	fprintf(stderr, "Usage: %s [-]{nio} <archive> [file] \n"
			"		-n	Number of sorting process to use(1-1000)\n"
			"		-i	 Input file for reading\n"
			"		-o	 Output file for writing\n", name);
	exit(EXIT_FAILURE);
}

void initalize() {
	int i;
	procces = malloc(sizeof(pid_t) * num_pro);
	sorter = malloc(sizeof(int*) * (num_pro));
	supper = malloc(sizeof(int*) * (num_pro));
	for (i = 0; i < (num_pro); ++i) {
		sorter[i] = malloc(sizeof(int) * 2);
		supper[i] = malloc(sizeof(int) * 2);
	}
}

int main(int argc, char **argv) {
	int kase;
	char* input = NULL;
	char* output = NULL;

	struct sigaction sig;

	sigemptyset(&sig.sa_mask);
	sig.sa_flags = 0;
	sig.sa_handler = handler;

	sigaction(SIGHUP, &sig, NULL);
	sigaction(SIGINT, &sig, NULL);
	sigaction(SIGQUIT, &sig, NULL);

	while ((kase = getopt(argc, argv, "n:i:o:")) != -1)
		switch (kase) {

		case 'n':	//Number of processes Defined
			num_pro = atoi(optarg);
			if (num_pro > 1000) {
				p_usage(argv[0]);
			}
			break;
		case 'i':	//Input defined
			input = optarg;
			break;
		case 'o':	//Output is defined
			output = optarg;
			break;
		default: 	// The ? case print usage
			p_usage(argv[0]);

		}
	if (argc < 2) {
		p_usage(argv[0]);
	}
	initalize();
	sort_func();
	if (input == NULL) {
		//printf("input == NULL\n");
		parser(input, 0);
	} else {
		//printf("input != NULL\n");
		parser(input, 1);
	}
	if (output == NULL) {
		//printf("output == NULL\n");
		fork_sup(output, 0);
	} else {
		//printf("output != NULL\n");
		fork_sup(output, 1);
	}
	//printf("NUM = %d IN = %s OUT = %s\n", num_pro, input, output);

	burn_kids();

	return 0;
}

