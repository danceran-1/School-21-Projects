CC = gcc
CFLAGS = -Wall -Wextra -std=c11

ifeq ($(MAKECMDGOALS), gcov_report)
	CFLAGS += --coverage
endif

ifeq ($(MAKECMDGOALS), test)
	CFLAGS += -DTESTING 
endif


$(EXECUTABLE): $(COBJ)
	$(CC) $(CFLAGS) -o $@ $^ -L$(BUILD_PATH) -lrt -ltetris -lncurses -lgcov

BUILD_PATH = ../build
SRC_DIR = brick_game/tetris
GUI_DIR = gui/cli
TEST_DIR = tests/

CSRC = $(wildcard $(SRC_DIR)/*.c) $(wildcard $(GUI_DIR)/*.c)
COBJ = $(patsubst %.c,$(BUILD_PATH)/%.o,$(notdir $(CSRC)))

LIBNAME = $(BUILD_PATH)/libtetris.a
EXECUTABLE = $(BUILD_PATH)/tetris

TEXI2DVI = texi2dvi
SOURCE =  docs/Tetris.texinfo
PROJECT = C7_BrickGame
VERSION = 1.0
TARFILE = $(PROJECT)-$(VERSION).tar.gz
GCOV_REPORT_DIR = gcov_report

.PHONY: all clean print_sources print_objects

all: clean install

$(LIBNAME): $(COBJ)
	mkdir -p $(BUILD_PATH)
	ar rcs $@ $^
	ranlib $@


$(BUILD_PATH)/%.o: $(SRC_DIR)/%.c | $(BUILD_PATH)
	$(CC) $(CFLAGS) -c $< -o $@ -g -lrt

$(BUILD_PATH)/%.o: $(GUI_DIR)/%.c | $(BUILD_PATH)
	$(CC) $(CFLAGS) -c $< -o $@ -g

$(EXECUTABLE): $(COBJ)
	$(CC) $(CFLAGS) -o $@ $^ -L$(BUILD_PATH) -lrt -ltetris -lncurses -lgcov

$(BUILD_PATH):
	mkdir -p $(BUILD_PATH)

install: $(LIBNAME)
	$(CC) -no-pie $(CFLAGS) -o $(BUILD_PATH)/$(EXECUTABLE) $(COBJ) -L$(BUILD_PATH) -lrt -ltetris -lncurses -lgcov

dvi: $(SOURCE)
	nano $(SOURCE)


	


Tetris_doc.dvi: docs/Tetris.texinfo
	$(TEXI2DVI) $<
	rm Tetris.log

dist: $(TARFILE)

$(TARFILE):
	mkdir -p $(PROJECT)-$(VERSION)
	cp -r brick_game $(PROJECT)-$(VERSION)/brick_game
	cp -r gui $(PROJECT)-$(VERSION)/gui
	cp -r docs/ $(PROJECT)-$(VERSION)/docs
	cp -r tests/ $(PROJECT)-$(VERSION)/tests
	cp Makefile $(PROJECT)-$(VERSION)/
	tar -czvf $(TARFILE) $(PROJECT)-$(VERSION)
	rm -rf $(PROJECT)-$(VERSION)

uninstall:
	rm -rf $(BUILD_PATH)

test:
	$(CC) $(CFLAGS) -fprofile-arcs -ftest-coverage -o $(TEST_DIR)/run_tests $(TEST_DIR)/tetris_test.c $(SRC_DIR)/tetris.c $(GUI_DIR)/interface.c -lncurses -lcheck -lsubunit -lm -g
	./$(TEST_DIR)/run_tests


gcov_report: clean $(LIBNAME)
	$(CC) $(CFLAGS) -DTESTING -fprofile-arcs -ftest-coverage $(TEST_DIR)/tetris_test.c $(SRC_DIR)/tetris.c  -o $(TEST_DIR)/run_tests -lncurses -lcheck -lsubunit -lm -lgcov
	./$(TEST_DIR)/run_tests
	lcov -t "tetris_test" -o $(TEST_DIR)/s21_test.info -c -d .
	
	genhtml -o report $(TEST_DIR)/s21_test.info
	rm -rf $(TEST_DIR)/*gcda $(TEST_DIR)/*gcno


clean:
	rm -rf $(BUILD_PATH)/*
	rm -rf report
	rm -rf C7_BrickGame-1.0.tar.gz
	rm -rf tetris.dvi
	rm -rf $(TEST_DIR)/*.o
	rm -rf $(TEST_DIR)/*.txt
	rm -rf $(TEST_DIR)/run_tests
	rm -rf $(TEST_DIR)/s21_test.info
	rm -rf Tetris.dvi
	rm -rf Tetris.toc
	rm -rf highscore.txt
