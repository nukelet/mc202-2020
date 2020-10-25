CFLAGS = -std=c99 -Wall -Werror -Werror=vla -g
LDFLAGS = -lm

.PHONY: all clean

all: calculadora

calculadora: calculadora.c
	gcc $(CFLAGS) calculadora.c -o calculadora $(LDFLAGS)

teste_big_int: teste_big_int.c
	gcc $(CFLAGS) big_int.c teste_big_int.c -o teste_big_int $(LDFLAGS)

clean:
	rm -f calculadora teste_big_int
