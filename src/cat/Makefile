CC = gcc -std=c11
FLAGS = -Werror -Wextra -Wall

all: s21_cat

s21_cat: s21_cat.o
	$(CC) $(FLAGS) $< -o $@

s21_cat.o: s21_cat.c
	$(CC) -c $(FLAGS) $< -o $@

check:
#	cppcheck *.h *.c
#	cp ../../materials/linters/CPPLINT.cfg CPPLINT.cfg
	python3 ../../materials/linters/cpplint.py --extension=c *.c *.h
#	CK_FORK=no leaks --atExit -- ./s21_cat
	
test: integration_tests.sh
	./integration_tests.sh
	
clean:
	rm -rf *.o random s21_cat