CC    ?= gcc
CFLAGS = -ansi -pedantic

manual :
	$(CC) -c $(CFLAGS) create_doc.c -o create_doc.o
	$(CC) create_doc.o -o create_doc
	./create_doc
	pdflatex flint-manual.tex
	bibtex flint-manual
	pdflatex flint-manual.tex
	pdflatex flint-manual.tex
	rm create_doc.o create_doc
	rm flint-manual.aux flint-manual.log flint-manual.out flint-manual.toc flint-manual.bbl flint-manual.blg

