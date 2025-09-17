CC = gcc
CFLAGS = -Wall -Wextra -g
TARGETS = lesson3_1 lesson3_2 lesson3_3 lesson3_4

all: $(TARGETS)

lesson3_1: lesson3_1.c
	$(CC) $(CFLAGS) -o $@ $<

lesson3_2: lesson3_2.c
	$(CC) $(CFLAGS) -o $@ $<

lesson3_2: lesson3_3.c
	$(CC) $(CFLAGS) -o $@ $<

lesson3_4: lesson3_4.c
	$(CC) $(CFLAGS) -o $@ $<

run1: lesson3_1
	./lesson3_1

run2: lesson3_2
	./lesson3_2

run3: lesson3_3
	./lesson3_3

run4: lesson3_4
	./lesson3_4

clean:
	rm -f $(TARGETS)