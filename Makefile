CC = gcc
CFLAGS = -Wall -Wextra -O2 -fPIC -DLEET_EXPORTS
LDFLAGS = -shared

all: libleetgen.so libleetgen.a

libleetgen.so: leet_generator.o
	$(CC) $(LDFLAGS) -o $@ $^

libleetgen.a: leet_generator.o
	ar rcs $@ $^

leet_generator.o: leet_generator.c leet_generator.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o *.so *.a

.PHONY: all clean
