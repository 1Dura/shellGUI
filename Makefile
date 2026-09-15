CFLAGS = -Wall -Wextra -Werror -std=c11

MAIN = src/window.c
OBJECTS = src/objects/*.c

TARGETS = launch test

all: $(TARGETS)

launch:
	gcc $(CFLAGS) $(MAIN) $(OBJECTS) -lncurses
	./a.out

test:
	echo "There s no tests yet, sorry :("

clean:
	rm -f a.out

rebuild: clean all

.PHONY: all launch test clean rebuild

