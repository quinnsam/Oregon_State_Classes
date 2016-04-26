Using the default Linux 3.0.4 kernel as described in HW2, you are asked to implement the following:

Write a RAM Disk device driver for the Linux Kernel which allocates a chunk of memory and presents it as a block device.

Using the Linux Kernel's Crypto API, add encryption to your block device such that your device driver encrypts and decrypts data when it is written and read. You will need to look at examples in the kernel for how to do this.

This will be developed in the drivers/block directory. Remember, as this is a block cypher, you may have more data than fits in one block of the cypher. Further, you need to be able to set the key as a module parameter.

A link you may find useful: http://lwn.net/Kernel/LDD3/.

The source repo from which to export is svn+ssh://os-class.engr.oregonstate.edu/scratch/cs411/linux. You will be using this source tree for the remainder of the projects.

You are also required to do the following:
    * Group write-up: Prepare a document containing the design you plan to use to implement the necessary algorithms.
    * Individual write-up: Answer the following questions in sufficient detail:
        1. What do you think the main point of this assignment is?
        2. How did you personally approach the problem? Design decisions, algorithm, etc.
        3. How did you ensure your solution was correct? Testing details, for instance.
        4. What did you learn?

Make sure your group submission is a tarball labelled CS444_project3_group#.tar.bz2 and includes the following:
    * A linux patch file containing your solution
    * The group write-up in LaTeX format.

Each individual will be required to submit their individual write-up in LaTeX format also conatined in a tarball labelled CS444_project3_writeup.tar.bz2
