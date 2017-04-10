CC = gcc
CFLAGS = -m32

all: main.c
	$(CC) $(CFLAGS) $< -o tvm379 -lm
	# ./tvm379 16 8 g 100 1000 f
	# To read the bin files type: hexdump -C quicksort-trace.bin | less
clean:
	rm -f *~ *.o tvm379
