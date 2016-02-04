TARGET=HW2
HTML=main_html
SRC={HW2}

default: all 

all:
	latex group_22_writeup.tex
	dvips -R -Poutline -t letter group_22_writeup.dvi -o group_22_writeup.ps
	ps2pdf group_22_writeup.ps
	rm group_22_writeup.aux
	rm group_22_writeup.dvi
	rm group_22_writeup.log
	rm group_22_writeup.out
	rm group_22_writeup.ps
