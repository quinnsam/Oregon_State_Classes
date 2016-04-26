TARGET=crypto
SRC={$TARGET}

default: all

all: pdf

dvi: ${TARGET}.tex 
	latex ${TARGET}.tex
	bibtex $(TARGET)
	latex $(TARGET).tex

ps: dvi
	dvips -R -Poutline -t letter ${TARGET}.dvi -o ${TARGET}.ps

pdf: ps
	ps2pdf ${TARGET}.ps
	rm ${TARGET}.aux
	rm ${TARGET}.dvi
	rm ${TARGET}.log
	rm ${TARGET}.out
	rm ${TARGET}.ps
	rm ${TARGET}.toc

	
