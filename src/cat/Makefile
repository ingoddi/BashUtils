CC = gcc
CFLAGS = -Wall -Werror -Wextra -std=c11 -g

build:
	$(CC) $(CFLAGS) s21_cat.c -o s21_cat

clean:
	rm -rf s21_cat log.txt s21_cat.dSYM

check:
	cppcheck s21_cat.c

test:
	bash test.sh

leaks:
	bash leaks.sh
