FILTER: FILTER.o filterFunctions.o
	gcc -o FILTER FILTER.o filterFunctions.o

FILTER.o: FILTER.c FILTER.h filterFunctions.h
	gcc -c filter.c

filterFunctions.o: filterFunctions.c filterFunctions.h FILTER.h
	gcc -c filterFunctions.c
