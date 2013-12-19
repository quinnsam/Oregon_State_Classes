TARGET=hw4_write_up
HTML=main_html
SRC={$TARGET}



default: all

all: pdf prog 

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


prog:
	icc thr_prime.c -o thread -w0 -pthread
	icc pro_prime.c -o pro -w0 -lrt