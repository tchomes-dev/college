CC = g++
CFLAGS = -Wall -Werror -pedantic
SFML = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
OBJS = TFractal.o Triangle.o
PROJ = TFractal

all: $(PROJ)

TFractal: $(OBJS)
	$(CC) $(OBJS) -o $(PROJ) $(SFML)

TFractal.o: TFractal.cpp
	$(CC) -c TFractal.cpp -o TFractal.o

Triangle.o: Triangle.cpp
	$(CC) -c Triangle.cpp Triangle.h $(CFLAGS)

clean:
	rm $(PROJ) $(OBJS)
