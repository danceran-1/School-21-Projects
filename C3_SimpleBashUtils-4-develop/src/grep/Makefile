CFLAGS= -c -Wall -Wextra -Werror
all: s21_grep clean

s21_grep: grep.o
	gcc grep.o -o s21_grep -lm

grep.o: grep.h grep.c
	gcc $(CFLAGS) grep.c

clean:
	rm -f *.o

rebuild: clean all
