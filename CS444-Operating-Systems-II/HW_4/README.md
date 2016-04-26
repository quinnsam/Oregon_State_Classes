Using the default Linux 3.0.4 kernel, you are asked to implement the following:

Understand how the SLOB first-fit alogorithm works and implement the best-fit allocation algorithm. You must also write a program that computes the effeciency of the first-fit algorithm and best-fit algorithm and compare the fragmentation sufferred by each algorithm.

This will be developed in the slob.c file in the mm directory.

The source repo from which to export is svn+ssh://os-class.engr.oregonstate.edu/scratch/cs411/linux. You will be using this source tree for the remainder of the projects.

You are also required to do the following:
    * Group write-up: Prepare a document containing the design you plan to use to implement the following algorithms.
    * Individual write-up: Answer the following questions in sufficient detail:
        1. What do you think the main point of this assignment is?
        2. How did you personally approach the problem? Design decisions, algorithm, etc.
        3. How did you ensure your solution was correct? Testing details, for instance.
        4. What did you learn?

Make sure your group submission is a tarball labelled CS411_project4_group#.tar.bz2 and includes the following:
    * A linux patch file containing your solution
    * The group write-up in LaTeX format.
    * A makefile for your write-up

Each individual will be required to submit their individual write-up in LaTeX format also conatined in a tarball labelled CS411_project4_writeup.tar.bz2 which should also include a makefile.
