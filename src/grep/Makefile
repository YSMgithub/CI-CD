CC = gcc -std=c11
FLAGS = -g -Wall -Wextra -Werror #-fsanitize=address -fsanitize=leak
all: s21_grep

s21_grep: s21_grep.o
	$(CC) $(FLAGS) $^ -o $@

s21_grep.o: s21_grep.c
	$(CC) -c $(FLAGS) $^ -o $@

test:
	./integration_test_grep.sh

check:
#	cppcheck *.h *.c
#	cp ../../materials/linters/CPPLINT.cfg CPPLINT.cfg
	python3 ../../materials/linters/cpplint.py --extension=c *.c *.h
#	valgrind -s --verbose --show-leak-kinds=all --leak-check=full ./s21_grep -e d -e 3 -e s text
#	CK_FORK=no leaks --atExit -- ./s21_grep 

clean:
	rm -rf s21_grep a.out s21_grep.o test_grep.o test_grep test text flags pattern myoutput.txt stand_out.txt