CC = gcc
CFLAGS = -Wall -Werror -Wextra -std=c11 -g

build:
	$(CC) $(CFLAGS) s21_grep.c -o s21_grep

clean:
	rm -rf s21_grep log.txt s21_grep.dSYM

check:
	cppcheck s21_grep.c

test:
	bash test.sh

leaks:
	bash leaks.sh

