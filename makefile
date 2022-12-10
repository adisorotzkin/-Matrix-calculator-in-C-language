mat: mymat.o mat.o
	gcc -g -ansi -Wall -pedantic mymat.o mat.o -o mymat
mymat.o: mymat.c mat.h
	gcc -c -ansi -Wall -pedantic mymat.c -o mymat.o
mat.o: mat.c mat.h
	gcc -c -ansi -Wall -pedantic mat.c -o mat.o
