all: main.o time.o commands.o signals.o
	gcc main.o time.o commands.o signals.o -o main

main.o: main.c
	gcc -c main.c

time.o: time.c
	gcc -c time.c

commands.o: commands.c
	gcc -c commands.c

signals.o: signals.c
	gcc -c signals.c
