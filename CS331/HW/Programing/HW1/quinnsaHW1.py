#!/usr/bin/env python
# -*- coding: utf-8 -*-
################################################################################
#	 ____                     ___        _            		       #
#	/ ___|  __ _ _ __ ___    / _ \ _   _(_)_ __  _ __  		       #
#	\___ \ / _` | '_ ` _ \  | | | | | | | | '_ \| '_ \ 		       #
#	 ___) | (_| | | | | | | | |_| | |_| | | | | | | | |		       #
#	|____/ \__,_|_| |_| |_|  \__\_\\__,_|_|_| |_|_| |_|		       #
#	 _   ___        __    _  _     _				       #
#	| | | \ \      / /  _| || |_  / |				       #
#	| |_| |\ \ /\ / /  |_  ..  _| | |				       #
#	|  _  | \ V  V /   |_      _| | |				       #
#	|_| |_|  \_/\_/      |_||_|   |_|                                      #
################################################################################
# Imports
import getopt
import sys
import os
import copy
from Queue import PriorityQueue

# Human readable state varibles
left = 0
right = 1
miss = 0
cann = 1
boat = 2
iddfs_counter = 0

def verify(state,verbose):
    if state[left][cann] > state[left][miss]:
        if state[left][miss]:
            return False
    if state[right][cann] > state[right][miss]:
        if state[right][miss]:
            return False
    return True

def expand(state,verbose):
    suc = []
    # Boat is on the left bank
    if state[left][boat] == 1:
        # Move one Missionary to right bank
        if state[left][miss] >= 1:
            temp = copy.deepcopy(state)
            temp[left][miss]  = temp[left][miss] -1
            temp[right][miss] = temp[right][miss] +1
            # Boat moved to other side
            temp[right][boat] = 1
            temp[left][boat]  = 0
            if verify(temp, verbose):
                if verbose:
                    print '[Valid] Move one Missionary to right bank'
                    print temp
                suc.append(temp)
            else:
                if verbose > 1: print '[Invalid] Move one Missionary to right bank'
        # Move two Missionaries to right bank
        if state[left][miss] >= 2:
            temp = copy.deepcopy(state)
            temp[left][miss]  = temp[left][miss] -2
            temp[right][miss] = temp[right][miss] +2
            # Boat moved to other side
            temp[right][boat] = 1
            temp[left][boat]  = 0
            if verify(temp, verbose):
                if verbose:
                    print '[Valid] Move two Missionaries to right bank'
                    print temp
                suc.append(temp)
            else:
                if verbose > 1: print '[Invalid] Move two Missionaries to right bank'
        # Move one Cannible to right bank
        if state[left][cann] >= 1:
            temp = copy.deepcopy(state)
            temp[left][cann]  = temp[left][cann] -1
            temp[right][cann] = temp[right][cann] +1
            # Boat moved to other side
            temp[right][boat] = 1
            temp[left][boat]  = 0
            if verify(temp, verbose):
                if verbose:
                    print '[Valid] Move one Cannible to right bank'
                    print temp
                suc.append(temp)
            else:
                if verbose > 1: print '[Invalid] Move one Cannible to right bank'
        # Move one Cannible and one Missionary to right bank
        if state[left][cann] >= 1 and state[left][miss] >= 1:
            temp = copy.deepcopy(state)
            temp[left][cann]  = temp[left][cann] -1
            temp[right][cann] = temp[right][cann] +1
            temp[left][miss]  = temp[left][miss] -1
            temp[right][miss] = temp[right][miss] +1
            # Boat moved to other side
            temp[right][boat] = 1
            temp[left][boat]  = 0
            if verify(temp, verbose):
                if verbose:
                    print '[Valid] Move one Cannible and one Missionary to right bank'
                    print temp
                suc.append(temp)
            else:
                if verbose > 1: print '[Invalid] Move one Cannible and one Missionary to right bank'
        # Move two Cannible to right bank
        if state[left][cann] >= 2:
            temp = copy.deepcopy(state)
            temp[left][cann]  = temp[left][cann] -2
            temp[right][cann] = temp[right][cann] +2
            # Boat moved to other side
            temp[right][boat] = 1
            temp[left][boat]  = 0
            if verify(temp, verbose):
                if verbose:
                    print '[Valid] Move two Cannible to right bank'
                    print temp
                suc.append(temp)
            else:
                if verbose > 1: print '[Invalid] Move two Cannible to right bank'

    # Boat is on the right bank
    if state[right][boat] == 1:
        # Move one Missionary to left bank
        if state[right][miss] >= 1:
            temp = copy.deepcopy(state)
            temp[right][miss] = temp[right][miss] -1
            temp[left][miss]  = temp[left][miss] +1
            # Boat moved to other side
            temp[left][boat]  = 1
            temp[right][boat] = 0
            if verify(temp, verbose):
                if verbose:
                    print '[Valid] Move one Missionary to left bank'
                    print temp
                suc.append(temp)
            else:
                if verbose > 1: print '[Invalid] Move one Missionary to left bank'
        # Move two Missionaries to left bank
        if state[right][miss] >= 2:
            temp = copy.deepcopy(state)
            temp[right][miss] = temp[right][miss] -2
            temp[left][miss]  = temp[left][miss] +2
            # Boat moved to other side
            temp[left][boat]  = 1
            temp[right][boat] = 0
            if verify(temp, verbose):
                if verbose:
                    print '[Valid] Move two Missionaries to left bank'
                    print temp
                suc.append(temp)
            else:
                if verbose > 1: print '[Invalid] Move two Missionaries to left bank'
        # Move one Cannible to left bank
        if state[right][cann] >= 1:
            temp = copy.deepcopy(state)
            temp[right][cann] = temp[right][cann] -1
            temp[left][cann]  = temp[left][cann] +1
            # Boat moved to other side
            temp[left][boat]  = 1
            temp[right][boat] = 0
            if verify(temp, verbose):
                if verbose:
                    print '[Valid] Move one Cannible to left bank'
                    print temp
                suc.append(temp)
            else:
                if verbose > 1: print '[Invalid] Move one Cannible to left bank'
        # Move one Cannible and one Missionary to left bank
        if state[right][cann] >= 1 and state[right][miss] >= 1:
            temp = copy.deepcopy(state)
            temp[right][cann] = temp[right][cann] -1
            temp[left][cann]  = temp[left][cann] +1
            temp[right][miss] = temp[right][miss] -1
            temp[left][miss]  = temp[left][miss] +1
            # Boat moved to other side
            temp[left][boat]  = 1
            temp[right][boat] = 0
            if verify(temp, verbose):
                if verbose:
                    print '[Valid] Move one Cannible and one Missionary to left bank'
                    print temp
                suc.append(temp)
            else:
                if verbose > 1: print '[Invalid] Move one Cannible and one Missionary to left bank'
        # Move two Cannible to left bank
        if state[right][cann] >= 2:
            temp = copy.deepcopy(state)
            temp[right][cann] = temp[right][cann] -2
            temp[left][cann]  = temp[left][cann] +2
            # Boat moved to other side
            temp[left][boat]  = 1
            temp[right][boat] = 0
            if verify(temp, verbose):
                if verbose:
                    print '[Valid] Move two Cannible to left bank'
                    print temp
                suc.append(temp)
            else:
                if verbose > 1: print '[Invalid] Move two Cannible to left bank'
    if verbose > 1:
        print 'Sucsessor'
        for i in suc:
            print '   ', i
    return suc

def print_sol(sol, mode):
    if not sol:
        print 'No solution avalible'
        sys.exit(1)

    f = open(mode + '_solution.txt', 'w')
    print 'Key:\nMissionarys  Cannibles  Boat'
    f.write('Key:\nMissionarys  Cannibles  Boat\n')
    print 'Left\t\tRight'
    f.write('Left\t\tRight\n')
    node_exp = sol.pop()
    for i in sol:
        print i[left][miss], i[left][cann], i[left][boat],'\t\t',i[right][miss], i[right][cann], i[right][boat]
        f.write(str(i[left][miss]) + ' ' + str(i[left][cann]) + ' ' + str(i[left][boat]) + '\t\t' + str(i[right][miss]) + ' ' + str(i[right][cann]) + ' ' + str(i[right][boat]) + '\n')
    print 'Total Moves:', len(sol), '\nTotal Nodes expanded:', node_exp
    f.write('Total Moves: ' + str(len(sol)) + '\nTotal Nodes expanded: ' + str(node_exp) + '\n')


def bfs(state, verbose):
    if verbose: print 'Breadth First Search'

    fringe = []
    closed = []
    nodes_exp = 0

    fringe.append(state[0])
    if verbose: print 'Current fringe', fringe
    while fringe != state[1]:
        if fringe == None: return False
        if verbose > 1:
            print "Fringe:"
            for i in fringe:
                print i
        if len(fringe):
            node = fringe.pop()
        else:
            print 'Not found'
            return False
        if node == state[1]:
            closed.append(node)
            if verbose > 1:
                for i in closed:
                    print i
            closed.append(nodes_exp)
            return closed
        nodes_exp = nodes_exp + 1
        if node not in closed:
            closed.append(node)
            for i in expand(node,verbose):
                fringe.insert(len(fringe),i)





def dfs(state, verbose):
    if verbose: print 'Depth First Search'

    fringe = []
    closed = []
    nodes_exp = 0

    fringe.insert(0, state[0])
    if verbose: print 'Current fringe', fringe
    while len(fringe):
        if verbose > 1:
            print "Fringe:"
            for i in fringe:
                print i
        node = fringe.pop(0)

        if node == state[1]:
            closed.append(node)
            if verbose > 1:
                for i in closed:
                    print i
            closed.append(nodes_exp)
            return closed
        nodes_exp = nodes_exp + 1
        if node not in closed:
            closed.append(node)
            for i in expand(node,verbose):
                fringe.insert(0,i)

    return False

def iddfs_dfs(node, depth, goal, visited, verbose):
    global iddfs_counter
    if depth == 0 and node == goal:
        if verbose: print 'Solution found:', visited
        visited.append(iddfs_counter)
        return visited
    elif depth > 0:
        iddfs_counter = iddfs_counter + 1
        for i in expand(node, verbose):
            if i not in visited:
                visited.append(i)
                temp = iddfs_dfs(i,depth -1, goal, visited, verbose)
                if temp:
                    return visited
    return []

def iddfs(state, verbose):
    if verbose: print 'Iterative depth First Search'

    closed = []
    itter = 0

    for itter in range(0,1000):
        closed = iddfs_dfs(state[0], itter, state[1], [], verbose)
        if len(closed):
            return closed


    return False

def h(node, verbose):
    if verbose > 1: print 'A-Star huristic function'
    lsum = 0
    rsum = 0
    for i in node[left]:
        lsum = lsum + i
    for i in node[right]:
        rsum = rsum + i

    return (rsum + lsum) - lsum

def astar(state, verbose):
    if verbose: print 'A-Star Search'

    fringe = []
    closed = []
    h_list = []
    nodes_exp = 0

    fringe.append(state[0])
    if verbose: print 'Current fringe', fringe
    while fringe != state[1]:
        if fringe == None: return False
        if verbose > 1:
            print "Fringe:"
            for i in fringe:
                print i
        if len(fringe):
            node = fringe.pop(0)
        else:
            print 'Not found'
            return False
        if node == state[1]:
            closed.append(node)
            if verbose > 1:
                for i in closed:
                    print i
            closed.append(nodes_exp)
            return closed
        nodes_exp = nodes_exp + 1
        if node not in closed:
            closed.append(node)
            for i in expand(node,verbose):
                h_list.append(h(node,verbose))
                fringe.insert(h(node,verbose),i)


def parse_state(init, goal, verbose):
    if verbose: print 'Parsing state file'
    # Check if file path exists
    if not os.path.isfile(init):
        print 'ERROR: ' + init + ' does not exist.'
        sys.exit(3)
    if not os.path.isfile(goal):
        print 'ERROR: ' + goal + ' does not exist.'
        sys.exit(3)

    state = []
    temp = []

    i = 0
    init_f = open(init,'r')
    for line in init_f.readlines():
        temp.append([])
        line = line.strip()
        for s in line.split(','):
            temp[i].append(int(s))
        i = i + 1

    state.append(temp)
    temp = []
    i = 0
    goal_f = open(goal,'r')
    for line in goal_f.readlines():
        temp.append([])
        line = line.strip()
        for s in line.split(','):
            temp[i].append(int(s))
        i = i + 1
    state.append(temp)

    if verbose:
        print 'State:'
        print '\tInital:'
        print '\t  Right Bank'
        print '\t    ', state[0][right]
        print '\t  Left Bank'
        print '\t    ', state[0][left]
        print '\tGoal:'
        print '\t  Right Bank'
        print '\t    ', state[1][right]
        print '\t  Left Bank'
        print '\t    ', state[1][left]

    return state


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
