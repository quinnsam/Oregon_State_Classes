#!/usr/bin/env python

def suffixPrefixPair1(x,y):
    left_sum  = 0
    right_sum = 0
    best_sum  = 10000000000
    indices = ()

    for j in xrange(len(x)-1, -1, -1):
        for k in xrange(0, len(y)):
            t = abs(x[j] + y[k])
            if t < best_sum:
                best_sum = t
                indices = (j, k)
    return indices

def suffixPrefixPair2(array_a, array_b):
    answer = () 
    sum_array_a=[0 for i in range(len(array_a))]
    sum_array_b=[0 for i in range(len(array_b))]

    for i in xrange(len(array_a)-1, -1, -1):
	if i == len(array_a)-1:
            sum_array_a[i] = (i, array_a[i], 'a')
        else:
            sum_array_a[i] = (i, array_a[i] + sum_array_a[i+1][1], 'a')

    for i in xrange(0, len(array_b), 1):
	if i == 0:
            sum_array_b[i] = (len(array_b)-1-i, array_b[i], 'b')
        else:
            sum_array_b[i] = (len(array_b)-1-i, array_b[i] + sum_array_b[i-1][1], 'b')

    sum_array_a = sorted(sum_array_a, key=lambda element: element[1])
    sum_array_b = sorted(sum_array_b, key=lambda element: element[1])

    ld = 10000000000

    for i in xrange(0, len(sum_array_a)):
        lld = 10000000000
        for j in xrange(0, len(sum_array_b)):
            t = abs(sum_array_a[i][1] + sum_array_b[j][1])
            if t < lld:
                lld = t
            else:
                if lld < ld:
                    ld = lld
                    answer = (ld, sum_array_a[i][0], sum_array_b[j][0])
                    break

    return answer

def suffixPrefixPair3(x, y):
    xtup = ()
    ytup = ()
    indices = ()
    a = []
    lowestDiff = 100000000000

    for i in range(0, len(y)-1):
        y[i] = y[i] * -1

    for i in range(0, len(x)):
        a.append((x[i], 'x', i))

    for i in range(0, len(y)):
        a.append((y[i], 'y', i))

    a = sorted(a, key=lambda element: element[0])

    for i in range(0, len(a)-2):
        localDiff = 1000000000000
        if a[i][1] == a[i+1][1]:
            continue
        else:
            localDiff = abs(a[i][0] + a[i+1][0])
            if localDiff < lowestDiff:
                lowestDiff = localDiff
       	        indices = (a[i][2], a[i+1][2])
    return indices 
 

def closestToZeroSubArray(x):
    if len(x) < 2:
	return abs(x[0])

    if len(x) == 2:
        return abs(x[0] + x[1])

    else:
	half = len(x) // 2
        firstHalf = x[:half]
        lastHalf = x[half:]

        return min(
            closestToZeroSubArray(firstHalf),
            closestToZeroSubArray(lastHalf),
	    suffixPrefixPair2(firstHalf, lastHalf)
        )		
