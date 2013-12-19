Project 2
====================
Project 2: UNIX file I/O and getting reacquainted with C

Due: Monday, 28 October 2013, 23:59:59

In this assignment, you will be working with UNIX file I/O system calls.
Write a C program (and yes, I mean C!) on os-class called myar.c. This program will illustrate the use of file I/O on UNIX by maintaining a UNIX archive library, in the standard archive format.
Once compiled your program should run in a manner similar to the standard UNIX command ar. You may wish to look at the man page for ar for insight, however, for this assignment, the following is the syntax your program must support:

myar key afile name ...

where afile is the name of the archive file to be used, and key is one of the following options (all are silent unless otherwise specified):

-v	iff specified with other options, print a verbose version of the output	 
-q	 quickly append named files to archive	  
-x	 extract named files	  
-t	 print a concise table of contents of the archive	  
-d	delete named files from archive	 
-A	 quickly append all ``regular'' files in the current directory	 (except the archive itself)
-w	 Extra credit: for a given timeout, add all modified files to the archive.	 (except the archive itself)

You must use getopt to parse the command line options (and only getopt -- do not use getopt_long).
The archive file maintained must use exactly the standard format defined in /usr/inc1ude/ar.h, and in fact may be tested with archives created with the ar command. The options listed above are compatible with the options having the same name in the ar command. -A is a new option not in the usual ar command.

Notes:
	1.For the -q command myar should create an archive file if it doesn't exist, using permissions ``666''. 	For the other commands myar reports an error if the archive does not exist, or is in the wrong format.

	2.You will have to use the system calls stat and utime to properly deal with extracting and restoring the 		proper timestamps. Since the archive format only allows one timestamp, store the mtime and use it to 		restore both the atime and mtime. Permissions should also be restored to the original value, subject to 	umask limitation.

	3.The -q and -A commands do not check to see if a file by the chosen name already exists. It simply 		appends the files to the end of the archive.
	
	4.The -x and -d commands operate on the first file matched in the archive, without checking for further 	matches.

	5.In the case of the -d option, you will have to build a new archive file to recover the space. Do this by 		unlinking the original file after it is opened, and creating a new archive with the original name.

	6.You are required to handle multiple file names as arguments.

	7.Since file I/O is expensive, do not make more than one pass through the archive file, an issue 		especially relevant to the multiple delete case.

	8.Compilation will be done with icc and use (at minimum) the following flags: '-std=c99 -Wall'.

	9.For the -w flag, the command will take as long as specified by the timeout argument. You should print 	out a status message upon adding a new file only if -v is specified. This may result in many different 		copies of the same file in the archive.

	10.For extra credit, any time a file is added that already exists, remove the old copy from the archive, 		but ONLY if it is not the same. If identical, do not add the new file. Size is NOT a valid indication of 		isomorphism. You will need to use a more advanced technique.

Your write-up should include (at minimum) the following:
	1.a design for your system, as well as places your implementation deviated from this design

	2.a work log, detailing what you did when -- this can fairly easily be created if you are using some form 		of revision control

	3.any challenges you overcame in completing this assignment

	4.answers to the following questions:
		1.What do you think the main point of this assignment is?

		2.How did you ensure your solution was correct? Testing details, for instance. This section should 			be very thorough.

		3.What did you learn?

Things to turn in:
	1.C source code
	2.write-up, as a tex document
	3.any support files necessary to compile your tex document or source
	4.a makefile to build both source code and your tex file

You are not allowed to use Lyx to create the document. You must create the document "by hand", instead.
