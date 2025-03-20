CC = gcc
CFLAGS = -O3

HEADERS = darr.h strus.h aesc.h

.PHONY = merge clean test run_test

default: all

all: merge clean test run_test

clean:
	rm test -f

test:
	$(CC) test.c -o test $(CFLAGS)

run_test:
	./test

merge:
	cat $(HEADERS) > utils.h
