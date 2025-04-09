LIB_NAME = s21_matrix_oop
CC = g++
FLAGS = -std=c++17 -Wall -Wextra -Werror
TEST_LIBS = -lgtest -lgtest_main -pthread
GCOV_FLAGS = -fprofile-arcs -ftest-coverage
LIBS = -lm

TESTS = ./tests/test_constructors.cpp ./tests/test_operators.cpp ./tests/test_gets_and_sets.cpp ./tests/test_methods.cpp ./tests/helper.cpp
TEST_EXECUTABLE = test_gtest

all: clean $(LIB_NAME).a test

$(LIB_NAME).o: clean
	@$(CC) $(FLAGS) $(LIBS) -c $(LIB_NAME).cpp

$(LIB_NAME).a: $(LIB_NAME).o
	@ar rc $(LIB_NAME).a $(LIB_NAME).o
	@rm -rf $(LIB_NAME).o

gcov_report: clean
	mkdir -p gcov
	$(CC) $(FLAGS) $(LIBS) $(GCOV_FLAGS) -c $(LIB_NAME).cpp
	ar rc $(LIB_NAME).a $(LIB_NAME).o
	$(CC) $(GCOV_FLAGS) $(TESTS) -o $(TEST_EXECUTABLE) $(LIB_NAME).a $(TEST_LIBS)
	./$(TEST_EXECUTABLE)
	gcov -o . $(LIB_NAME).cpp
	mv *.gcov gcov/

lcov: clean gcov_report
	@lcov --capture --directory . --output-file coverage.info
	@genhtml coverage.info --output-directory lcov
	@xdg-open lcov/index.html

$(TEST_EXECUTABLE): $(TESTS) $(LIB_NAME).a
	@$(CC) $(FLAGS) $(TESTS) -o $(TEST_EXECUTABLE) $(LIB_NAME).a $(TEST_LIBS)

debug: $(TEST_EXECUTABLE)
	gdb test_gtest

test: $(TEST_EXECUTABLE)
	./$(TEST_EXECUTABLE)

style:
	cppcheck --enable=all --suppress=missingIncludeSystem ./
	clang-format -n -style=google *.cpp *.h ./tests/*.cpp ./tests/*.h

valgrind: $(TEST_EXECUTABLE)
	chmod +rwx ./test_gtest
	valgrind --trace-children=yes --track-fds=yes --track-origins=yes --leak-check=full --show-leak-kinds=all -s ./test_gtest --no-nfs-check

clean:
	@rm -rf $(LIB_NAME).a $(LIB_NAME).o
	@rm -rf $(TEST_EXECUTABLE)
	@rm -rf gcov lcov
	@rm -rf test_gtest* *.gcda *.gcno
	@rm -rf coverage.info
