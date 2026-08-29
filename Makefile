CC = gcc
CFLAGS = -Wall -Wextra -std=c11
TARGET = mandel
OBJECTS = main.o mandelmath.o

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(TARGET) -lm

maths.o : mandelmath.c mandelmath.h
	$(CC) $(CFLAGS) -c mandelmath.c

main.o: main.c mandelmath.h
	$(CC) $(CFLAGS) -c main.c

clean:
	rm -f *.o $(TARGET)