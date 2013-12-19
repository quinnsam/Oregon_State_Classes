/*********************************************************************
 ** Program Filename: myar.c
 ** Author: Sam Quinn
 ** Date: 10/30/2013
 ** Description: Mimics ar command
 *********************************************************************/

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/utsname.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>
#include <ar.h>
#include <time.h>
#include<math.h>
 #include <dirent.h>


#define BLOCKSIZE 1
#define STR_SIZE sizeof("rwxrwxrwx")
#define FP_SPECIAL 1

int oct_dec(int num) {
	long int decimal = 0;
	int i = 0;

	while (num != 0) {
		decimal = decimal + (num % 10) * pow(8, i++);
		num = num / 10;
	}

	return decimal;
}

char *filePermStr(mode_t perm, int flags) {
	static char str[STR_SIZE];
	snprintf(str, STR_SIZE, "%c%c%c%c%c%c%c%c%c", (perm & S_IRUSR) ? 'r' : '-',
			(perm & S_IWUSR) ? 'w' : '-',
			(perm & S_IXUSR) ?
					(((perm & S_ISUID) && (flags & FP_SPECIAL)) ? 's' : 'x') :
					(((perm & S_ISUID) && (flags & FP_SPECIAL)) ? 'S' : '-'),
			(perm & S_IRGRP) ? 'r' : '-', (perm & S_IWGRP) ? 'w' : '-',
			(perm & S_IXGRP) ?
					(((perm & S_ISGID) && (flags & FP_SPECIAL)) ? 's' : 'x') :
					(((perm & S_ISGID) && (flags & FP_SPECIAL)) ? 'S' : '-'),
			(perm & S_IROTH) ? 'r' : '-', (perm & S_IWOTH) ? 'w' : '-',
			(perm & S_IXOTH) ?
					(((perm & S_ISVTX) && (flags & FP_SPECIAL)) ? 't' : 'x') :
					(((perm & S_ISVTX) && (flags & FP_SPECIAL)) ? 'T' : '-'));
	return str;
}

int comp(char* name_2, int in_fd, int offset) {
	char name_buf[16];
	char name[16];
	int comp = 0;
	int eof, readd, i, j;
	lseek(in_fd, offset, SEEK_SET);
	//printf("OFFSET <%d>", offset); // problems here

	readd = read(in_fd, name_buf, 16);
	if (readd == -1) {
		perror("Can't read input file");
		exit(-1);

	}

	for (i = 0; i < 16; i++) {
		if (name_buf[i] == '/') {
			eof = i;
			//printf("WHILE(%c-%d)\n", name_buf[i], i);
			break;
		} else {
			//Do nothing
		}

	}

	for (j = 0; j < eof; j++) {
		name[j] = name_buf[j];
	}
	name[eof] = '\0';

	if (strcmp(name, name_2) == 0) {
		comp = 1;
	}
	return comp;

}

void extract(char *afile, char *name, int flag, int verb) {

	//printf("AFILE = %s NAME =%s \n", afile, name);
	int in_fd, out_fd;
	int nread, nwrite;
	int size, offset = SARMAG;
	int end;
	off_t file_size;

	in_fd = open(afile, O_RDONLY);
	if (in_fd == -1) {
		perror("Can't open input file");
		exit(-1);
	}

	file_size = lseek(in_fd, 0, SEEK_END);

	while (print_name(in_fd, offset, 0) == 0) {
		//printf("WhileLLLOOPP");
		if (comp(name, in_fd, offset) == 1) {
			//printf("SIZE == %d", print_size(in_fd, offset));
			size = print_size(in_fd, offset);
			offset += 60;

			break;
		}
		if (print_size(in_fd, offset) % 2 == 0) {
			//printf("yeah\n");
			offset += print_size(in_fd, offset) + 60;
		} else {

			offset += print_size(in_fd, offset) + 61;
		}

		if (offset >= file_size) {
			if (verb ==1){
				printf("No Member Named `%s'\n", name);

			}
			exit(-1);

			break;
		}

	}

	//printf("FILE = %s, SIZE = %d, START = %d \n", name, size, offset);

	/*####################################-Extract-########################*/
	if (flag == 1) {
		if(verb == 1){
				printf("x - %s\n", name);
			}
		char *extr[size];

		lseek(in_fd, offset, SEEK_SET);
		nread = read(in_fd, extr, size);

		out_fd = open(name, O_WRONLY | O_CREAT, 0666);

		if (out_fd == -1) {
			perror("Canot open/create output file2");
			exit(-1);
		}
		nwrite = write(out_fd, extr, nread);
		if (nwrite != nread) {
			perror("Error writing file.");
			exit(-1);
		}

	}
	/*####################################-Delete-########################*/
	if (flag == 2) {
		//offset = offset;
		if(verb == 1){
				printf("d - %s\n", name);
			}
		if (size % 2 != 0) {
			++size;
		}

		char buf[offset - 60];
		char buf2[file_size - offset - size];
		int i = 0;
		off_t copied = 0;
		int orig = offset;
		//lseek(in_fd, offset, SEEK_SET);

		lseek(in_fd, 0, SEEK_SET);

		//while (copied < file_size-size - 60) {
		//printf("OFFSET %d\n", offset);
		nread = read(in_fd, buf, orig - 60);
		if (nread == offset - 60) {
			offset += size + 60;
			//printf("SIZE == %ld\n", file_size-offset-size);
			lseek(in_fd, offset - 60, SEEK_SET);
			nread = read(in_fd, buf2, file_size - orig - size);

		}

		out_fd = open(afile, O_WRONLY | O_TRUNC);
		if (out_fd == -1) {
			perror("Canot open/create output file2");
			exit(-1);
		}
		nwrite = write(out_fd, buf, orig - 60);
		if (nwrite == -1) {
			perror("Write error: ");
			exit(-1);
		}
		nwrite = write(out_fd, buf2, file_size - orig - size);
		if (nwrite == -1) {
			perror("Write error: ");
			exit(-1);
		}
		//unlink(afile);

		//	}

	}

}

int is_ar(char* file) {
	int in_fd;
	char ar[SARMAG - 1];

	in_fd = open(file, O_RDONLY);
	if (in_fd == -1) {
		return -1;
	}

	read(in_fd, ar, SARMAG - 1);
//printf("STRING IS %s\n", ar);
	if (strcmp(ar, "!<arch>") == 0) {

		//printf("This is a Archive\n");
		return 0;
	} else
		//printf("This is not and archive +%s+\n" , ar);
		return -1;

}
void print_ugid(int in_fd, int offset) {
	char ugid_buf[6];
	char ugid[6];
	int k, o, i, j, readd, eof;

	for (k = 0; k < 2; ++k) {
		if (k == 0) {
			o = 28;
		} else {
			o = 34;
		}

		lseek(in_fd, offset + o, SEEK_SET);

		readd = read(in_fd, ugid_buf, 6);
		if (readd == -1) {
			perror("Can't read input file");
			exit(-1);

		}

		for (i = 0; i < 6; i++) {
			if (ugid_buf[i] == ' ') {
				eof = i;
				break;
			} else {
				//do nothing
			}
		}

		for (j = 0; j < eof; j++) {
			ugid[j] = ugid_buf[j];
		}
		//ugid[6] = '\0';
		printf("%s", ugid);
		if (k == 0) {
			printf("/");
		} else {
			printf("    ");
		}

	}
}

void print_date(int in_fd, int offset) {
	char date_buf[12];
	char date[12];
	char buffe[80];
	struct tm ts;
	int i, j, readd;
	time_t tim;

	lseek(in_fd, offset + 16, SEEK_SET);

	readd = read(in_fd, date_buf, 12);
	if (readd == -1) {
		perror("Can't read input file");
		exit(-1);

	}

	for (i = 0; i < 12; i++) {
		if (date_buf[i] == ' ') {
			break;
		} else {
			//do nothing
		}
	}

	for (j = 0; j < 12; j++) {
		date[j] = date_buf[j];
	}
//date[12] = '\0';
	tim = (long) atoi(date);
	ts = *localtime(&tim);

	strftime(buffe, sizeof(buffe), "%b %d %H:%M %Y ", &ts);
	printf("%s", buffe);

}

int print_name(int in_fd, int offset, int print) {
//printf("file== %s\n", file[2]);
//printf("IN FUN");
	char name_buf[16];
	char name[16];
	int is_next = 0;
	int eof, readd, i, j;

	is_next = -1;
	lseek(in_fd, offset, SEEK_SET);
//printf("OFFSET <%d>", offset); // problems here

	readd = read(in_fd, name_buf, 16);
	if (readd == -1) {
		perror("Can't read input file");
		exit(-1);

	}

	for (i = 0; i < 16; i++) {
		if (name_buf[i] == '/') {
			eof = i;
			is_next = 0;
			//printf("WHILE(%c-%d)\n", name_buf[i], i);
			break;
		} else {
			//Do nothing
		}

	}
	if (is_next == -1) {
		return is_next;
	}

	for (j = 0; j < eof; j++) {
		name[j] = name_buf[j];
	}
	name[eof] = '\0';

	if (print == 1) {
		printf("%s\n", name);
	}
	return is_next;
}

int print_size(int in_fd, int offset) {
	char size_buf[10];
	char size[10];
	int i, j, eof, readd;

	lseek(in_fd, offset + 48, SEEK_SET);

	readd = read(in_fd, size_buf, 10);
	if (readd == -1) {
		perror("Can't read input file");
		exit(-1);

	}

	for (i = 0; i < 10; i++) {
		if (size_buf[i] == ' ') {
			eof = i;
			break;
		} else {
			//do nothing
		}
	}

	for (j = 0; j < eof; j++) {
		size[j] = size_buf[j];
	}
	size[eof] = '\0';
	return atoi(size);
}

char* print_mode(int in_fd, int offset) {
	char mode_buf[8];
	char mode[8];
	int mod;
	int i, j, eof, readd;

	lseek(in_fd, offset + 40, SEEK_SET);

	readd = read(in_fd, mode_buf, 8);
	if (readd == -1) {
		perror("Can't read input file");
		exit(-1);

	}

	for (i = 0; i < 8; i++) {
		if (mode_buf[i] == ' ') {
			eof = i;
			break;
		} else {
			//do nothing
		}
	}

	for (j = 2; j < eof; j++) {

		mode[j - 2] = mode_buf[j];
		//printf("CHAR == %c", mode_buf[j]);
	}
	mod = atoi(mode);
//printf("MODE = %d\n", mod);
	mode[eof] = '\0';
//printf("%s ", filePermStr(oct_dec(mod), 2));
//printf("MODE == %d.\n", mod);

	return filePermStr(oct_dec(mod), 2);
}

void display(char* file[], int verb, int flag, int argc) {
	int in_fd, readd, i, arg_num = 0;
	int eof, j;
	char *input = file[2];
	int offset = SARMAG;
	off_t file_size;

	in_fd = open(input, O_RDONLY);
	if (in_fd == -1) {
		perror("Can't open input file");
		exit(-1);
	}

	file_size = lseek(in_fd, 0, SEEK_END);

	if (is_ar(input) == -1) {
		printf("%s is not an archive.\n", input);
		exit(-1);
	}

	if (verb != 1) {

		while (print_name(in_fd, offset, 0) == 0) {
			print_name(in_fd, offset, 1);
			if (print_size(in_fd, offset) % 2 == 0) {
				offset += print_size(in_fd, offset) + 60;
			} else {
				offset += print_size(in_fd, offset) + 61;
			}

			if (offset >= file_size) {
				break;
			}
			//printf("OFF == %d,\n", offset);

		}
	} else if (verb == 1) {
		while (print_name(in_fd, offset, 0) == 0) {
			printf("%s ", print_mode(in_fd, offset));
			print_ugid(in_fd, offset);
			printf("%d ", print_size(in_fd, offset));
			print_date(in_fd, offset);
			print_name(in_fd, offset, 1);
			if (print_size(in_fd, offset) % 2 == 0) {
				offset += print_size(in_fd, offset) + 60;
			} else {
				offset += print_size(in_fd, offset) + 61;
			}

			if (offset >= file_size) {
				break;
			}
			//printf("OFF == %d,\n", offset);

		}
	}
}


void create_ar(char* file, char* afile, int verb) {
	int out_fd, in_fd, k, i = 3;
	struct ar_hdr* arch = malloc(sizeof(struct ar_hdr));
	//printf("file== %s", file);

	struct stat *stat_file = malloc(sizeof(struct stat));

	int num_read;
	if(verb == 1){
		printf("a - %s\n", file);
	}


	if (stat(file, stat_file) == -1) {
		perror("Error in Stat");
		exit(-1);
	}
	out_fd = open(afile, O_WRONLY | O_APPEND);
	//printf("FD_OUT++%d", out_fd);
	if (out_fd == -1) {
		//perror("Canot open/create output file1");

		out_fd = open(afile, O_CREAT | O_WRONLY | O_APPEND, 0666);

		if (out_fd == -1) {
			perror("Canot open/create output file2");
			exit(-1);
		}
		write(out_fd, ARMAG, SARMAG);
	}

	sprintf(arch->ar_name, "%s/%-16s", file, "");
	sprintf((arch->ar_date), "%-12ld", (long) stat_file->st_mtime);
	//printf("%ld bitch \n", stat_file->st_mtime);
	sprintf((arch->ar_uid), "%-6ld", (long) stat_file->st_uid);
	sprintf((arch->ar_gid), "%-6ld", (long) stat_file->st_gid);
	sprintf((arch->ar_mode), "%-8lo", (unsigned long) stat_file->st_mode);
	sprintf((arch->ar_size), "%-10lld", (long long) stat_file->st_size);
	sprintf((arch->ar_fmag), "%s\n", ARFMAG);

	//printf("MODE =!= %ld\n", (long) stat_file->st_mode);

	write(out_fd, arch, sizeof(struct ar_hdr));

	char buf[(long long) stat_file->st_size];

	in_fd = open(file, O_RDONLY);
	if (in_fd == -1) {
		perror("Can't open input file");
		exit(-1);
	}
	num_read = read(in_fd, buf, sizeof(buf));
	//printf("%s\n", buf);

	write(out_fd, buf, num_read);
	if (stat_file->st_size % 2 != 0) {
		write(out_fd, "\n", 1);
	}
	//printf("ohyeah");
	/*
	 printf("%s\n", arch->ar_name);
	 printf("UID= %s\n", arch->ar_uid);
	 printf("GID= %s\n", arch->ar_gid);
	 printf("MODE= %s\n", arch->ar_mode);
	 printf("SIZE= %s\n", arch->ar_size);
	 printf("Last file modification:   %s\n", arch->ar_date); // stat_file->st_mtime);
	 */

}
char *strip_chars(char *string, const char *chars)
{
  char * newstr = malloc(strlen(string) + 1);
  int counter = 0;

  for ( ; *string; string++) {
    if (!strchr(chars, *string)) {
      newstr[ counter ] = *string;
      ++ counter;
    }
  }

  newstr[counter] = 0;
  return newstr;
}

void all(char* afile, char* exe, int verb){
	if(is_ar(afile) == -1){
		printf("%s is not an archive\n", afile);
		exit(-1);
	}
	DIR *dirp;
	    struct dirent *dp;
	    char* cur;
	    char* exe1 = strip_chars(exe, "./");


	    if ((dirp = opendir(".")) == NULL) {
	        perror("couldn't open Directory");
	        exit(-1);
	    }


	   while ((dp = readdir(dirp)) != 0){
		   cur = dp->d_name;
		   //printf ("EXE%s\n\n", exe1);

	           if (strcmp(dp->d_name, afile) == 0 || strcmp(exe1, dp->d_name) == 0){
	            	//do nothing
	        	   //printf("ARCHIVE == %s", dp->d_name);
	            } else if(dp->d_type == DT_REG && dp->d_type != DT_DIR){
	            	create_ar(cur, afile, verb);
	            }


	        }



	   /* if (errno != 0)
	        perror("error reading directory");
	    else
	        (void) printf("failed to find %s\n", arg);
	    (void) closedir(dirp);
	    return;*/
}

int main(int argc, char **argv) {
	int fname;		//Location of filename arguments in argv[]
	int kase;

	char *arg[argc];

	struct ar_hdr *arch = malloc(sizeof(struct ar_hdr));

	int verb = 0;

	while ((kase = getopt(argc, argv, "vq:x:t:d:A:")) != -1)
		switch (kase) {
		case 'v':
			verb = 1;
			break;
		case 'q':

			optind--;
			for (; optind < argc && *argv[optind] != '-'; optind++) {
				arg[optind] = argv[optind];
				//printf("%s num= %d\n", arg[optind], optind);
				if (optind > 2) {
					create_ar(arg[optind], arg[2], verb);
				}
			}

			break;
		case 'x':

			optind--;
			for (; optind < argc && *argv[optind] != '-'; optind++) {
				arg[optind] = argv[optind];
				//printf("%s num= %d\n", arg[optind], optind);
				if (optind > 2) {
					extract(arg[2], arg[optind], 1, verb);
				}
			}
			//display(arg, arch, SARMAG, verb, 1, argc);
			break;
		case 't':
			//printf("HEY %d\n\n", verb);

			optind--;
			for (; optind < argc && *argv[optind] != '-'; optind++) {
				arg[optind] = argv[optind];
				//printf("%s num= %d\n", arg[optind], optind);
			}
			display(arg, verb, 2, argc);
			break;
		case 'd':

			optind--;
			for (; optind < argc && *argv[optind] != '-'; optind++) {
				arg[optind] = argv[optind];
				//printf("%s num= %d\n", arg[optind], optind);
				if (optind > 2) {
					extract(arg[2], arg[optind], 2, verb);
				}
			}
			break;
		case 'A':
			all(argv[2], argv[0], verb);

			break;
		default: /* '?' */
		                   fprintf(stderr, "Usage: %s [-]{vqxtdAw} <archive> [file] \n"
									"		-v	if specified with other options, print a verbose version of the output\n"
									"		-q	 quickly append named files to archive\n"
									"		-x	 extract named files\n"
									"		-t	 print a concise table of contents of the archive\n"
									"		-d	delete named files from archive\n"
									"		-A	 quickly append all ``regular'' files in the current directory (except the archive itself)\n",
		                           argv[0]);
		                   exit(EXIT_FAILURE);

		}



	return 0;
}

