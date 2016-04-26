import csv
import time
from closest_to_zero import closestToZeroSubArray

if __name__ == "__main__":
    runtimes = open('runtimes.txt', 'a')
    test_cases = open('test_cases_without_solutions.csv', 'rb')

    spamreader = csv.reader(test_cases)
    for row in spamreader:
        array = eval(row[0])
        runtimes.write("{0}".format(len(array)))
        avg = 0
        for i in range(0,4):
            start = time.time()
            answer = closestToZeroSubArray(array)
            end = time.time()

            milliseconds = (end - start) * 1000
            avg += milliseconds

            runtimes.write(", {1}".format(len(array), milliseconds))
        avg = avg/4
        runtimes.write("\t{0}\n".format(avg))
