#!/usr/bin/env python
# -*- coding: utf-8 -*-
################################################################################
#	 ____                     ___        _            		       #
#	/ ___|  __ _ _ __ ___    / _ \ _   _(_)_ __  _ __  		       #
#	\___ \ / _` | '_ ` _ \  | | | | | | | | '_ \| '_ \ 		       #
#	 ___) | (_| | | | | | | | |_| | |_| | | | | | | | |		       #
#	|____/ \__,_|_| |_| |_|  \__\_\\__,_|_|_| |_|_| |_|		       #
#        _   ___        __    _  _     ____                                    #
#       | | | \ \      / /  _| || |_  |___ \                                   #
#       | |_| |\ \ /\ / /  |_  ..  _|   __) |                                  #
#       |  _  | \ V  V /   |_      _|  / __/                                   #
#       |_| |_|  \_/\_/      |_||_|   |_____|                                  #
################################################################################
# Imports
import getopt
import sys
import os

def usage():
    print sys.argv[0] + "  <igmo>||<init,goal,mode,output> [ahv] [all,help]"
    print "\t-i,--init\t\tInital state"
    print "\t-g,--goal\t\tGoal state"
    print "\t-m,--mode\t\tSearch mode"
    print "\t\t* bfs   (for breadth-first search)"
    print "\t\t* dfs   (for depth-first search)"
    print "\t\t* iddfs (for iterative deepening depth-first search)"
    print "\t\t* astar (for A-Star search below)"
    print "\t-a,--all\t\tAll search modes"
    print "\t-v\t\t\tVerbose output"
    print "\t-vv\t\t\tVery Verbose output"
    print "\t-h,--help\t\tPrint usage message"

def main():

    # Get all command line arguments
    try:
        opts, args = getopt.getopt(sys.argv[1:], "i:g:m:vha", ["all", "help", "init=", "goal=", "mode="])
    except getopt.GetoptError as err:
        # print help information and exit:
        print str(err) # will print something like "option -a not recognized"
        usage()
        sys.exit(2)
    goal_file = None
    init_file = None
    verbose = 0
    all_search = False
    mode = None
    for o, a in opts:
        if o == "-v":
            verbose = verbose + 1
        elif o in ("-h", "--help"):
            usage()
            sys.exit()
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
            usage()
            sys.exit(2)


    state = parse_state(init_file, goal_file, verbose)

    # Determine which search to run
    if all_search:
        print "BFS"
        print_sol(bfs(state, verbose), 'bfs')
        print "DFS"
        print_sol(dfs(state, verbose), 'dfs')
        print "IDDFS"
        print_sol(iddfs(state, verbose), 'iddfs')
        print "A-Star"
        print_sol(astar(state, verbose), 'astar')
    elif mode == 'bfs':
        print_sol(bfs(state, verbose), mode)
    elif mode == 'dfs':
        print_sol(dfs(state, verbose), mode)
    elif mode == 'iddfs':
        print_sol(iddfs(state, verbose), mode)
    elif mode == 'astar':
        print_sol(astar(state, verbose), mode)
    elif mode == None and all_search == False:
        usage()


if __name__ == "__main__":
        main()
