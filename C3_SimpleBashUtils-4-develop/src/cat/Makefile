CFLAGS= -c -Wall -Wextra -Werror
all: s21_cat clean

s21_cat: cat.o
	gcc cat.o -o s21_cat -lm

cat.o: cat.h cat.c
	gcc $(CFLAGS) cat.c

clean:
	rm -f *.o

rebuild: clean all
