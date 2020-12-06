CC=gcc
CFLAGS=-I. -lm -fopenmp -Wall --std=c99
DEPS = Dijkstra.h Graph.h Node.h PriorityQueue.h timer.h
OBJ = Dijkstra.o Graph.o PriorityQueue.o timer.o

main: $(OBJ) main.o
	$(CC) -o $@ $^ $(CFLAGS)

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

clean:
	\rm -f *.o main main.exe *~ *#
