CC = g++
OBJS = hw1.o
PROJ = hw1

all: $(PROJ)

hw1: $(OBJS)
	$(CC) $(OBJS) -o $(PROJ) $(VFLAGS)

hw1.o: hw1.c
	$(CC) -c hw1.c -o hw1.o

clean:
	rm $(PROJ) $(OBJS)
