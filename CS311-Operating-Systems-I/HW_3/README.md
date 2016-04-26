Project 3 
====================
CS 311: Project 3 
UNIX Process control 
Due 13 November 2013, 23:59:59

Write a C program called uniqify. uniqify's job is to read a text file and output the unique words in the file, sorted in alphabetic order. The input is from stdin, and the output is to stdout.

Internally, the program would be organized into 3 types of processes. A single process reads the input parsing the lines into words, another group of process does the sorting, and a single process suppresses duplicate words and writes the output. You should organize the processes so that every parent waits for its children.

You must use the system sort command (/bin/sort) with no arguments to do the actual sorting, and your program must arrange to start the processes and plumb the pipes (this means no popen). The number of sorting processes is a command line argument to the program, with the parser distributing the words round robin to the sorting processes (just like dealing cards).

The I/O to and from the pipes should be done using the stream functions fgets and fputs, with fdopen for attaching to the pipes, and fclose for flushing the streams. After each sorting process is done, work must still be done to merge and uniquify the words prior to printing the list from the suppresser.

In this assignment words are all alphabetic and case insensitive, with the parser converting all alphabetic characters to lower case. Any non-alphabetic characters delimit words and are discarded.

All processes should terminate cleanly on INTR, QUIT, and HANGUP signals. This requires the installation of a signal handler for each of these three signals. Ensure you do this via sigaction, rather than signal. Also, ensure you issue QUIT signals to all children, as well.

You are responsible for cleaning up any mess you make on the server. I do not want to see anyone with 1000 processes, all of which are hanging.

You must use getopt and reasonable options for setting the number of sorting processes, the name of the input file, and the name of the output file. If no input or output files are specified, read and write via standard output.

Please provide timings based on the size of the input file. Ensure that you test it with multiple types and sizes of files, including word lists and free form prose. These timings should be plotted in a fashion that makes sense. I recommend using one of matlab, gnuplot, R, or octave to generate the plot. Please ensure to save the plot as a postscript file.

Things to turn in:
	1.C/C++ source code for the solution to the posed problem.

	2.A makefile to build your code and your write-up

	3.A postscript file containing your timings plot.

	4.Your write-up, which contains the same content as necessary in Assignment 2.

For extra credit, provide output similar to uniq -c, where each word is output with its frequency. To receive full extra credit, you have to calculate this "on the fly" -- no storing all the words in memory.

Special note: please do not forget to include function headers for each function in your code. As a rule, I should not have to scroll to read a function, and it should be performing a single task, no more.
