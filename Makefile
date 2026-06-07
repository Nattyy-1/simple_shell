CC = gcc
CFLAGS = -Wall -Werror -Wextra -pedantic -std=gnu89
SRC = $(wildcard *.c)
OBJ = $(SRC:.c=.o)
NAME = hsh

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) -o $(NAME)

%.o: %.c main.h
	$(CC) $(CFLAGS) -c $< -o $@

betty:
	betty *.c *.h

test: $(NAME)
	./tests/run_tests.sh

test-mem:
	$(CC) -Wall -Wextra -g -fsanitize=address,leak -std=gnu89 $(SRC) -o $(NAME)
	./tests/run_tests.sh
	$(MAKE) re

clean:
	$(RM) $(NAME) $(OBJ)

re: clean all

.PHONY: all betty test test-mem clean re
