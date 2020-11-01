CFLAGS = -std=c99 -Wall -Werror -Werror=vla -g
LDFLAGS = -lm

.PHONY: all clean

all: calculadora

calculadora: calculadora.c
	gcc $(CFLAGS) calculadora.c big_int.c -o calculadora $(LDFLAGS)

# teste_big_int: teste_big_int.c
# 	gcc $(CFLAGS) big_int.c teste_big_int.c -o teste_big_int $(LDFLAGS)

# teste_sum: teste_sum.c
# 	gcc $(CFLAGS) big_int.c teste_sum.c -o teste_sum $(LDFLAGS)

# teste_subtract: teste_subtract.c
# 	gcc $(CFLAGS) big_int.c teste_subtract.c -o teste_subtract $(LDFLAGS)

# teste_multiply: teste_multiply.c
# 	gcc $(CFLAGS) big_int.c teste_multiply.c -o teste_multiply $(LDFLAGS)

# teste_divide: teste_divide.c
# 	gcc $(CFLAGS) big_int.c teste_divide.c -o teste_divide $(LDFLAGS)

# teste_copy: teste_copy.c
# 	gcc $(CFLAGS) big_int.c teste_copy.c -o teste_copy $(LDFLAGS)

clean:
	rm -f calculadora # teste_copy teste_big_int teste_sum teste_subtract teste_multiply teste_divide
