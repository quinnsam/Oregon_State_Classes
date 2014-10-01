In this project you will be developing your solution on the supplied hardware. Using a modified Linux 3.0.4 Kernel, you are asked to implement the following:
    * Implement the Round Robin process scehduling algorithm
    * Implement the First-In First-Out(FIFO) process scheduling algorithm

For this class, we will be operating within a CentOS 6.5 i386 environment. You will need to install some software on the supplied machine. Specifically, run the following command:

sudo yum groupinstall "Additional Development" "Desktop Platform Development" "Development tools"

You can pick up the hardware (if you have not already done so) in DB205. The TAs will be there on and off for the next couple days.

You will be required to make use of subversion to obtain this and all subsequent projects. Export the kernel to use from our (read-only) repository at the URL 

svn+ssh://os-class.engr.oregonstate.edu/scratch/cs411/project1

Ensure that you use the 'export' command to svn. Create a new source control repo on os-class under the /scratch/groupXX directory. Please ensure you replace XX with your group number. This will be the master copy for your group. As you work, ensure each of you is committing your work to this repo periodically. Choice of version control software is up to you, but you MUST maintain a centrol repository.

See here for instructions on working with files (specifically subversion repos) in a group setting. This is, in my opinion, the easiest method.

You are not required to develop your solution on the provided machine, however when you demo your solution, it must be done via the provided machine. TO receive full credit,

You are also required to do the following:
    * Group write-up: Prepare a document containing the design you plan to use to implement the following algorithms.
    * Individual write-up: Answer the following questions in sufficient detail:
        1. What do you think the main point of this assignment is?
        2. How did you personally approach the problem? Design decisions, algorithm, etc.
        3. How did you ensure your solution was correct? Testing details, for instance.
        4. What did you learn?
    * Version control log (formatted as a table) -- there are any number of tools for generating a TeX table from repo logs

Make sure your group submission is a tarball labelled CS444_project1_group#.tar.bz2 and includes the following:
    * A linux patch file containing your solution
    * The group write-up in LaTeX format.
Each individual will be required to submit their individual write-up in LaTeX format also conatined in a tarball labelled CS444_project1_writeup.tar.bz2
