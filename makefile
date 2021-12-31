all: main.o
	gcc -o main main.o

main: main.c
	gcc -c main.c

run:
	./main

clean:
	rm *.o