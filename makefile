CC = gcc
CFLAGS = -O3 -Wall

HEADERS = asprintf.h darr.h strus.h aesc.h mem.h

.PHONY = merge clean test run_test

default: all

all: merge clean test run_test

clean:
	rm -f test

test:
	$(CC) test.c -o test $(CFLAGS)

run_test:
	./test

merge:
	cat $(HEADERS) > utils.h
