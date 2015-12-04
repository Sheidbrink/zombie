CC = g++
CFLAGS = -g -pthread -I. -O3
LIBS = -lm -lglut -lGL -lGLU -lgsl -lgslcblas
SRC = main.c
OBJ = $(SRC:.c=.o)

default:
	$(CC) $(CFLAGS) $(SRC) -o lab1.o $(LIBS) 
clean:
	rm -f *.o
