OBJS = misc.o desktop.o comandos.o lista.o
CFLAGS = -Wall -Wextra -g3

all: teste 

teste: $(OBJS) principal.c
	gcc $(CFLAGS) $(OBJS) principal.c -o teste

clean:
	rm -f $(OBJS) t

.PHONY: all clean
