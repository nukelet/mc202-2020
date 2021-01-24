CFLAGS = -std=c99 -Wall -Werror -Werror=vla -g
LDFLAGS = -lm

CPPFLAGS = -std=c++14 -Wall

.PHONY: all clean

all: caminho

# caminho: caminho.c
# 	gcc $(CFLAGS) *.c -o caminho $(LDFLAGS)

# caminho: lugia.cpp
# 	g++ $(CPPFLAGS) lugia.cpp -o caminho $(LDFLAGS)

caminho: main.c
	gcc $(CFLAGS) main.c safe_allocators.c -o caminho $(LDFLAGS)

clean:
	rm -f caminho
