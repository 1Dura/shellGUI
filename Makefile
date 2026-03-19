CFLAGS = -Wall -Wextra -Werror -std=c11

SRC = src/*.c

TARGETS = launch test

all: $(TARGETS)

launch:
	gcc $(CFLAGS) $(SRC) -lncurses
	./a.out

test:
	echo "There s no tests yet, sorry :("

clean:
	rm -f a.out

rebuild: clean all

.PHONY: all launch test clean rebuild

