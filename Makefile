CC = gcc
CFLAGS = -Wall -Wextra -O2 -fPIC
LDFLAGS = -shared

all: libleet.so libleet.a leet_demo
libleet.so: leet_generator.o
	$(CC) $(LDFLAGS) -o $@ $^
libleet.a: leet_generator.o
	ar rcs $@ $^
leet_demo: main.o libleet.so
	$(CC) -o $@ main.o -L. -l:libleet.so
leet_generator.o: leet_generator.c leet_generator.h
	$(CC) $(CFLAGS) -c $< -o $@
main.o: main.c leet_generator.h
	$(CC) $(CFLAGS) -c $< -o $@
run: leet_demo
	LD_LIBRARY_PATH=. ./leet_demo
clean:
	rm -f *.o *.so *.a leet_demo

.PHONY: all run clean
