CC = gcc
CFLAGS = -Wall -Wextra -O2 -fPIC
LDFLAGS = -shared

all: libleet.so libleet.a leet_demo

libleet.so: leet_generator.o
	$(CC) $(LDFLAGS) -o $@ $^

libleet.a: leet_generator.o
	ar rcs $@ $^

leet_demo: main.o libleet.so
	$(CC) -o $@ main.o -L. -l:libleet.so -Wl,-rpath,.

leet_generator.o: leet_generator.c leet_generator.h
	$(CC) $(CFLAGS) -c $< -o $@

main.o: main.c leet_generator.h
	$(CC) $(CFLAGS) -c $< -o $@ -Wno-format

clean:
	rm -f *.o *.so *.a leet_demo

run: leet_demo
	./leet_demo

.PHONY: all run clean
