CC = gcc
CFLAGS = -m32

all: main.c
	$(CC) $(CFLAGS) $< -o tvm379
	./tvm379 16 8 g 100 1000 f trace1

clean:
	rm -f *~ *.o tvm379
