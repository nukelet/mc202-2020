CFLAGS = -std=c99 -Wall -Werror -Werror=vla -g
LDFLAGS = -lm

.PHONY: all clean

all: corretor

corretor: main.c
	gcc $(CFLAGS) *.c -o corretor $(LDFLAGS)

clean:
	rm -f corretor
