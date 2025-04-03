CC = gcc
CFLAGS = -Wall -Wextra -std=c99
DEPS = order.h utils.h metrics.h
OBJ = main.o utils.o metrics.o

app1: $(OBJ)
	$(CC) -o $@ $^

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

clean:
	rm -f *.o app1
