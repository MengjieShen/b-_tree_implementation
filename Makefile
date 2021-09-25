CC  = gcc

CFLAGS  = -g 

main: main.c function.o dictionary.o insertion.o tree.h
	$(CC) $(CFLAGS) -o main main.c function.o insertion.o dictionary.o

insertion.o: insertion.c tree.h
	$(CC) $(CFLAGS) -c insertion.c

dictionary.o: dictionary.c tree.h
	$(CC) $(CFLAGS) -c dictionary.c

function.o: function.c tree.h
	$(CC) $(CFLAGS) -c function.c

run: main
	./main -k 3 -f "4batch-30000.csv"

clean:
	rm -f *~ *.o a.out core main