import os
import sys
import math
def make_dir():
	term = raw_input("Term: ")
	clas = raw_input("Class: ")
	if os.path.exists(term + '/' + clas)==0: # Checks if directorys exist 0=NO
		os.makedirs(term +'/'+ clas)  #creates a directory term with a subdirectory class
		os.chdir(term + '/' + clas)
		os.mkdir('assignments')
		os.mkdir('exmples')
		os.mkdir('exams')
		os.mkdir('lecture_notes')
		os.mkdir('submissions')
		#os.mkdir('handin')
		if os.path.exists('/usr/local/classes/eecs/' +term+'/'+clas+'/public_html') == 0:
			os.symlink('/usr/local/classes/eecs/' +term+'/'+clas+'/public_html', 'website')
		if os.path.exists('/usr/local/classes/eecs/' +term+'/'+clas+'/handin') == 0:
			os.symlink('/usr/local/classes/eecs/' +term+'/'+clas+'/handin', 'handin')
		print "Your Directories have been made and smbolic links linked"

	else:
		print "The directories you were trying to create have already been created!"
def large():
	number= "7316717653133062491922511967442657474235534919493496983520312774506326239578318016984801869478851843858615607891129494954595017379583319528532088055111254069874715852386305071569329096329522744304355766896648950445244523161731856403098711121722383113622298934233803081353362766142828064444866452387493035890729629049156044077239071381051585930796086670172427121883998797908792274921901699720888093776657273330010533678812202354218097512545405947522435258490771167055601360483958644670632441572215539753697817977846174064955149290862569321978468622482839722413756570560574902614079729686524145351004748216637048440319989000889524345065854122758866688116427171479924442928230863465674813919123162824586178664583591245665294765456828489128831426076900422421902267105562632111110937054421750694165896040807198403850962455444362981230987879927244284909188845801561660979191338754992005240636899125607176060588611646710940507754100225698315520005593572972571636269561882670428252483600823257530420752963450"
	n_1 = 0
	l = 5
	i = 0
	while l <= len(number):
		n_2 = 1
		for a in range (i,l):
			n_2 *= int(number[a])
		if n_2 > n_1:
			n_1=n_2
		i=i+1
		l=l+1
	print "The largest number is: ", n_1

letters = {'A':1,'B':2,'C':3,'D':4,'E':5,'F':6,'G':7,'H':8,'I':9,'J':10,'K':11\
         ,'L':12,'M':13,'N':14,'O':15,'P':16,'Q':17,'R':18,'S':19,'T':20,'U':21\
         ,'V':22,'W':23,'X':24,'Y':25,'Z':26}
def names():
	r = open('names.txt', 'rU')
	name =[]
	name = sorted (r.read().replace('"', '').split(','), key=str)

	
	l = len(name)
	x = 0
	for i in range (0,(l)):
		#print "MAN"
		m = 0
		n = 0
		for alpha in name[i]:
			j = letters[alpha]
			m = m + l
		n = m * (i+1)
		x = x + n
	print "The sum of all the names scores is = ", x
	
def triangle():

	r = open('words.txt','r')
	words = r.read().split(',')
	words = [list(w.strip('\"')) for w in words]
	r.close()

	largest = max([len(w) for w in words])

	tri_nums = [n*(n + 1)/2 for n in range(1,2*largest)]
	 
	tri_words = 0
	for w in words:
	    if sum([letters[alpha] for alpha in w]) in tri_nums:
		tri_words += 1
	 
	print "I found %s triangle words in this document." % (tri_words)

def main():
	"""print what would you like me to do for you?
		1) Make directors for a new class and term.
		2) Find the largest concecutive number.
		3) Alphibeticaly sort and rate names.
		4) Find triangle words.
	"""
	#option = raw_input()
	if len(sys.argv) < 2:
		print "you did not give any arguments"

	else:
		if sys.argv[1] == '1':
			make_dir()
		if sys.argv[1] == '2':
			large()
		if sys.argv[1] == '3':
			names()
		if sys.argv[1] == '4':
			triangle()
		if sys.argv[1] > '4':
			print"You have entered an invalid argument."
main()
