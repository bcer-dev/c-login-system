CC=gcc -g

all: src/*.c
	$(CC) $^ -o bin/login