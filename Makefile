CC = gcc
CFLAGS = -Wall -Werror -Wextra -std=c11 
GCOVFLAGS = -ftest-coverage -fprofile-arcs
TESTFLAGS = -lcheck

OS := $(shell uname)
ifeq ($(OS), Linux)
    TESTFLAGS += -lm -lrt -lsubunit -lpthread
endif

SOURCE = s21_*.c 
HEADER = s21_matrix.h
OBJECTS= $(patsubst %.c, %.o, $(SOURCE))

TESTS_SOURCE = $(wildcard ./tests/test_*.c)
TESTS_OBJECTS = $(patsubst ./tests/%.c, ./tests/%.o, ${TESTS_SOURCE})
TESTS_HEADER = ./test_includes/s21_tests.h

all: s21_matrix.a gcov_report

s21_matrix.a: $(SOURCE) $(HEADER)
	$(CC) $(CFLAGS) -c $(SOURCE)
	ar rc s21_matrix.a $(OBJECTS)
	ranlib s21_matrix.a
	rm -rf *.o


test: s21_matrix.a main.c ${TESTS_SOURCE} $(TESTS_HEADER) 
	$(CC) $(CFLAGS) main.c ${TESTS_SOURCE} $(TESTFLAGS) s21_matrix.a -o atest
	./atest
	rm -rf *.o *.a atest

gcov_report: main.c  ${SOURCE} $(HEADER) $(TESTS_HEADER) ${TESTS_SOURCE}
	$(CC) $(CFLAGS) $(GCOVFLAGS) main.c ${TESTS_SOURCE} $(TESTFLAGS) ${SOURCE}  -o test
	./test
	lcov -t "test" -o test_report.info -c -d .
	genhtml -o report test_report.info
	rm -rf *.o *.gcno *.gcda *.info test

open:
	open report/index.html


clean:
	rm -rf *.o *.gcno *.a *.gcda
	rm -rf ./report/ *.info
	rm -rf test_report test

re:	clean all

.PHONY: all test gcov_report clean
