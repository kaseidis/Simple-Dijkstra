CC=gcc
GENERALFLAGS = -fopenmp -Wall 
CFLAGS= --std=c99
LINKFLAGS = -I. -lm
DEPS = Dijkstra.h Graph.h Node.h PriorityQueue.h timer.h
OBJ = Dijkstra.o Graph.o PriorityQueue.o timer.o

ifeq ($(OS),Windows_NT)
    LINKFLAGS += -fPIC -static -static-libgcc -static-libstdc++ 
endif

main: $(OBJ) main.o
	$(CC) -o $@ $^ $(LINKFLAGS) $(GENERALFLAGS)

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS) $(GENERALFLAGS)

clean:
	\rm -f *.o main main.exe *~ *#
