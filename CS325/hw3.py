#!/usr/bin/env python



def meth_1():
    x = [31, -41, 59, 26, -53]
    y = [58, -6, 97, -93, -23]

    left_sum  = 0
    right_sum = 0
    best_sum  = 10000000000

    for j in xrange(len(x)-1, 0, -1):
        #left_sum += x[j]
        for k in range(0, len(y)-1):
            #right_sum += y[k]
            #t = abs(left_sum + right_sum)
            t = abs(x[j] + y[k])
            if t < best_sum:
                best_sum = t
        #right_sum = 0

    return best_sum

def meth_2():
    x = [-53, -27, -9, 22, 32]
    y = [33, 52, 56, 58, 149]

    x.sort()
    y.sort()

    #xindex = Null
    #yindex = Null
    lowestDiff = 10000000000

    for j in range(0, len(x)-1):
        lld = 10000000000
        for k in range(0, len(y)-1):
            t = abs(x[j] + y[k])
            if t < lld:
                lld = t
            else:
                if lld < lowestDiff:
                    lowestDiff = lld
                    break
    return lowestDiff


def meth_3():
    x = [-53, -27, -9, 22, 32]
    y = [33, 52, 56, 58, 149]

    xtup = ()
    ytup = ()
    a = []
    lowestDiff = 100000000000

    for i in range(0, len(y)-1):
        y[i] = y[i] * -1

    for i in range(0, len(x)-1):
        a.append((x[i], 'x'))

    for i in range(0, len(y)-1):
        a.append((y[i], 'y'))

    a = sorted(a, key=lambda element: element[0])
    for i in range(0, len(a)-2):
        localDiff = 1000000000000
        if a[i][1] == a[i+1][1]:
            continue
        else:
            localDiff = abs(a[i][0]) + a[i+1][0]
            if localDiff < lowestDiff:
                lowestDiff = localDiff
    return lowestDiff












def main():
    print "Method 1:", meth_1()
    print "Method 2:", meth_2()
    print "Method 3:", meth_3()

if __name__ == "__main__":
    main()
