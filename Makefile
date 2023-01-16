CC = gcc
CFLAGS = -Wall -std=c99

all: sort grade sudoku

sort: ex12q1.c
	$(CC) $(CFLAGS) -D SORT ex12q1.c lab12.h  -o sorting

grade: ex12q1.c
	$(CC) $(CFLAGS) -D GRADE ex12q1.c lab12.h -o grading


sudoku: ex12q2.c
	$(CC) $(CFLAGS) ex12q2.c -o ex12q2

clean:
	rm sorting grading ex12q2
