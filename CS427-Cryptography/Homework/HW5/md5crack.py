import hashlib
import os
import thread

dog_hashs = [None] * 1000000
cat_hashs = {}
threads = [0] * 16
def createMD5(cat, start, end, thread):
    for i in range(0, start -1):
        cat = cat + '\x00'
    for i in range(start, end):
        cat = cat + '\x00'
        cat_hashs[hashlib.md5(cat).hexdigest()[:10]] = i
    print 'Thread ['+str(start)+']['+str(end)+'] finished'
    threads[thread] = 1

def checkMD5(dog, start, end, thread):
    for i in range(0, start - 1):
        dog = dog + '\x00'
    for i in range(start, end):
        dog = dog + '\x00'
        dh = hashlib.md5(dog).hexdigest()[:10]
        try:
            cat_ans = cat_hashs[dh]
            print 'Fount at cat[' + str(cat_ans) + '] dog[' + str(i) + '] (' + dh + ')'
        except KeyError:
            continue
        print 'Thread ['+str(start)+']['+str(end)+'] finished'
        threads[thread] = 0


def main():
    n = (1000000 - 0 + 1) / 16
    # Create two threads as follows
    c = open('cat.jpg', 'r')
    cat = c.read()
    d = open('dog.jpg', 'r')
    dog = d.read()
    c.close()
    d.close()

    try:
        for i in range(0, 16):
            thread.start_new_thread( createMD5, (cat, i * n, (i+1) * n, i))
    except Exception as e:
        print "Error: unable to start thread", str(e)

    run = True
    while run:
       count = 0
       for i in threads:
           count += i
       if count > 15:
           run = False
       pass

    print 'Out of looop finding colisions'
    try:
        for i in range(0, 16):
            thread.start_new_thread( checkMD5, (dog, i * n, (i+1) * n, i))
    except Exception as e:
        print "Error: unable to start thread", str(e)

    run = True
    while run:
       count = 0
       for i in threads:
           count += i
       if count == 0:
           run = False
       pass

    #col = [x for x in dog_hashs if x in cat_hashs]
    #dog_answer = dog_hashs.index(col)
    #cat_answer = cat_hashs.index(col)

    #print 'Finding index in dog'
    #for i in range(0, dog_answer):
    #    dog = dog + '0'
    #print 'Finding index in cat'
    #for i in range(0, cat_answer):
    #    cat = cat + '0'

    #f = open('cat_crack.jpg', 'rw+')
    #f.write(cat)
    #f.close()
    #f = open('dog_crack.jpg', 'rw+')
    #f.write(dog)
    #f.close()



if __name__ == "__main__":
    main()
