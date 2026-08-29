CC = gcc
CFLAGS = -Wall -Wextra -std=c11
TARGET = mandelbrot
OBJECTS = main.o mandelmath.o mandelgraph.o

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(TARGET) -lm

mandelmath.o : mandelmath.c header.h
	$(CC) $(CFLAGS) -c mandelmath.c

mandelgraph.o : mandelgraph.c header.h
	$(CC) $(CFLAGS) -c mandelgraph.c

main.o: main.c header.h
	$(CC) $(CFLAGS) -c main.c

clean:
	rm -f *.o $(TARGET)