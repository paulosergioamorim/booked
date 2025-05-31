build: *.c
	gcc *.c -o main -Wall

debug: *.c
	gcc *.c -o main -g -Wall