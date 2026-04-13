simulation.exe : main.o simulation.o pqueue.o BigInt.o
	gcc -std=c99 -o simulation.exe main.o simulation.o pqueue.o BigInt.o

main.o : main.c simulation.h
	gcc -c -std=c99 main.c

simulation.o : simulation.c simulation.h pqueue.h BigInt.h
	gcc -c -std=c99 simulation.c

pqueue.o : pqueue.c pqueue.h
	gcc -c -std=c99 pqueue.c

BigInt.o : BigInt.c BigInt.h
	gcc -c -std=c99 BigInt.c