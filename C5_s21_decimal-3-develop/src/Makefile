CC = gcc
FLAGS = -std=c11 -Wall -Wextra -Werror
SOURCE = s21_decimal.c
OBJECT = $(patsubst %.c,%.o, $(SOURCE))
TEST = tests/tests.c

ifeq ($(shell uname),Darwin)
CHECKFLAGS = -lcheck
else
CHECKFLAGS = -lcheck -lm -lsubunit
endif

all: s21_decimal.a

s21_decimal.a:
	$(CC) -c $(FLAGS) $(SOURCE)
	ar rcs s21_decimal.a $(OBJECT)
	rm -rf *.o

test: clean
	$(CC) $(FLAGS) -o test --coverage $(SOURCE) $(TEST) $(CHECKFLAGS)
	./test
	rm -rf *.gcno *gcda *.gco *.o *.a

gcov_report: clean
	gcc -std=c11 -Wall -Wextra -Werror -o test --coverage s21_decimal.c tests/tests.c -lcheck -lm -lsubunit
	./test
	lcov -t "test" -o test.info --no-external -c -d .
	genhtml -o report test.info
	open report/index.html
	rm -rf *.gcno *gcda *.gco *.o *.a

style:
	cppcheck --enable=all --suppress=missingIncludeSystem ./
	clang-format -n -style=google *.c *.h ./tests/*.c


valgrind: test
	chmod +rwx ./test
	valgrind --trace-children=yes --track-fds=yes --track-origins=yes --leak-check=full --show-leak-kinds=all -s ./test --no-nfs-check

clean:
	rm -rf *.a *.gcno *.gcda coverage_html *.o *.test *.info test report
