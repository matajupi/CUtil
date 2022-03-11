CC=gcc
CFLAGS=-Werror -std=c11

testm: bin/testm
	./bin/testm

bin/testm: bin/cmemory.o bin/testm.o
	$(CC) $(LDFLAGS) -o $@ $^

bin/cmemory.o: cmemory.h cmemory.c
	$(CC) $(CFLAGS) -o $@ -c cmemory.c

bin/testm.o: testm.c
	$(CC) $(CFLAGS) -o $@ -c testm.c

clean:
	rm -rf bin
	mkdir bin

.PHONY: clean test
