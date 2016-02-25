import hashlib
import os
import thread

def createMD5(cat, start, end):
    for i in range(start, end):
        cat = cat + '\x00'
        if hashlib.md5(cat).hexdigest()[:10] == '6ee0184681':
            print 'found'
            return cat

def main():
    c = open('cat.jpg', 'r')
    cat = c.read()
    d = open('dog.jpg', 'r')
    dog = d.read()
    c.close()
    d.close()

    cat1 = createMD5(cat, 0, 1000000)
    dog1 = createMD5(dog, 0, 1000000)
    f = open('cat_crack.jpg', 'rw+')
    f.write(cat1)
    f.close()
    f = open('dog_crack.jpg', 'rw+')
    f.write(dog1)
    f.close()



if __name__ == "__main__":
    main()
