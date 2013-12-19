TARGET=copy
TARGET_1=questions
HTML=main_html
SRC={$TARGET}



default: all

all: pdf questions sieve python 

dvi: ${TARGET}.tex 
#	pygmentize the input source file -- THIS NAME SHOULD BE SAFE
#	pygmentize -f latex -o __${TARGET}.tex ${TARGET}.tex
#	run latex twice to get references correct
	latex ${TARGET}.tex
#	you can also have a bibtex line here
#	bibtex $(TARGET)
	latex $(TARGET).tex
#	remove the pygmentized output to avoid cluttering up the directory
#	rm __${TARGET}.tex

ps: dvi
	dvips -R -Poutline -t letter ${TARGET}.dvi -o ${TARGET}.ps

pdf: ps
	ps2pdf ${TARGET}.ps
	rm ${TARGET}.aux
	rm ${TARGET}.dvi
	rm ${TARGET}.log
	rm ${TARGET}.out
	rm ${TARGET}.ps


html:
	cp ${TARGET}.tex ${HTML}.tex
	latex ${HTML}.tex
	latex2html -split 0 -noshow_section_numbers -local_icons -no_navigation -noinfo -noaddress ${HTML}

	sed 's/<BR><HR>//g' < ${HTML}/index.html > ${HTML}/index2.html
	mv ${HTML}/index2.html ${TARGET}.html
	rm ${HTML}.*
	rm -rf ${HTML}
questions: 
	latex ${TARGET_1}.tex
	latex ${TARGET_1}.tex
	dvips -R -Poutline -t letter ${TARGET_1}.dvi -o ${TARGET_1}.ps
	ps2pdf ${TARGET_1}.ps
	rm ${TARGET_1}.aux
	rm ${TARGET_1}.dvi
	rm ${TARGET_1}.log
	rm ${TARGET_1}.out
	rm ${TARGET_1}.ps

sieve:
	icc sieve.c -o sieve
	./sieve

python:
	python Hw.py 1
	python Hw.py 2
	python Hw.py 3
	python Hw.py 4
