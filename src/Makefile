CC = gcc
GCOV = -fprofile-arcs -ftest-coverage
REPORTDIR = gcovdir
FILE_LIB = s21_math
FILE1 = s21_math_test

OS = $(shell uname)

ifeq ($(OS),Darwin)
    CHECKFLAGS=-lcheck
else
    CHECKFLAGS=-lcheck -lpthread -lrt -lm -lsubunit
endif

all: clean s21_math.a

s21_math.a: s21_math.c
	$(CC) -c s21_math.c -o s21_math.o 
	ar rcs s21_math.a s21_math.o

test: s21_math.a
	$(CC) -c s21_math_test.c -o s21_math_test.o 
	$(CC) s21_math_test.o s21_math.o $(CHECKFLAGS) -o s21_math_test

	./s21_math_test

gcov_report: s21_math.a
	rm -rf *.o *.a *.gcno *.gcda *.gcov *.info $(REPORTDIR)
	$(CC) $(GCOV) s21_math_test.c $(CHECKFLAGS) s21_math.c -o $(FILE_LIB) 

	./$(FILE_LIB)
	lcov -t "Unit-tests of $(FILE_LIB)" -o $(FILE_LIB).info -c -d .
	genhtml -o $(REPORTDIR) $(FILE_LIB).info

clean:
	rm -rf *.o *.a *.gcno *.gcda *.gcov *.info $(REPORTDIR) s21_math_test s21_math
