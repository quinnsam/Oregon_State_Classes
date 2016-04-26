#include <stdio.h>
#include <sys/types.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>

#define BLOCKSIZE 1

int main(int argc, char **argv)
{
	char *input = argv[1];
	char *output = argv[2];

	int in_fd;
	int out_fd;

	char buf[BLOCKSIZE];

	int num_read;
	int num_written;

	off_t file_size;
	off_t copied;

	in_fd = open(input, O_RDONLY);
	if(in_fd == -1){
		perror("Can't open input file");
		exit(-1);
	}

	out_fd = open(output, O_WRONLY | O_CREAT, 0777);
	if(out_fd == -1){
		perror("Can't open output file");
		exit(-1);
	}
	
	file_size = lseek(in_fd, 0, SEEK_END);
	copied = 0;
	lseek(in_fd, -1, SEEK_END);

	while(copied < file_size){
		num_read = read(in_fd, buf, BLOCKSIZE);
		num_written = write(out_fd, buf, BLOCKSIZE);

		if (num_read != num_written){
			perror("Error writing file");
			unlink(output);
			exit(-1);
		}

		copied += num_written;

		lseek(in_fd, -2, SEEK_CUR);
	}
	
	return 0;
}
