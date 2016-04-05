#!/usr/bin/env python
# -*- coding: utf-8 -*-

# Imports
import getopt
import sys

def bfs(verbose):
    if verbose: print 'Breadth First Search'

def dfs(verbose):
    if verbose: print 'Depth First Search'

def iddfs(verbose):
    if verbose: print 'Iterative depth First Search'

def astar(verbose):
    if verbose: print 'A-Star Search'


def usage():
    print sys.argv[0] + "  <igmo>||<init,goal,mode,output> [ahv] [all,help]"
    print "\t-i,--init\t\tInital state"
    print "\t-g,--goal\t\tGoal state"
    print "\t-m,--mode\t\tSearch mode"
    print "\t\t* bfs   (for breadth-first search)"
    print "\t\t* dfs   (for depth-first search)"
    print "\t\t* iddfs (for iterative deepening depth-first search)"
    print "\t\t* astar (for A-Star search below)"
    print "\t-o,--output\t\tOutput file"
    print "\t-a,--all\t\tAll search modes"
    print "\t-v\t\t\tVerbose output"
    print "\t-h,--help\t\tPrint usage message"

def main():
    try:
        opts, args = getopt.getopt(sys.argv[1:], "i:g:m:o:vha", ["all", "help", "init=", "goal=", "mode=", "output="])
    except getopt.GetoptError as err:
        # print help information and exit:
        print str(err) # will print something like "option -a not recognized"
        usage()
        sys.exit(2)
    output = None
    goal_file = None
    init_file = None
    verbose = False
    all_search = False
    mode = None
    for o, a in opts:
        if o == "-v":
            verbose = True
        elif o in ("-h", "--help"):
            usage()
            sys.exit()
        elif o in ("-o", "--output"):
            output = a
        elif o in ("-i", "--init"):
            init_file = a
        elif o in ("-g", "--goal"):
            goal_file = a
        elif o in ("-m", "--mode"):
            mode = a
        elif o in ("-a", "--all"):
            all_search = True
        else:
            assert False, "unhandled option"

        if all_search:
            bfs(verbose)
            dfs(verbose)
            iddfs(verbose)
            astar(verbose)
        elif mode == 'bfs':
            bfs(verbose)
        elif mode == 'dfs':
            dfs(verbose)
        elif mode == 'iddfs':
            iddfs(verbose)
        elif mode == 'astar':
            astar(verbose)
        elif mode == None and not all_search:
            usage()


if __name__ == "__main__":
        main()
