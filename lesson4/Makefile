CC = gcc
CFLAGS = -Wall -Wextra -g -pthread
TARGETS = lesson4_1 lesson4_2 lesson4_3 lesson4_4

all: $(TARGETS)

lesson4_1: lesson4_1.c
	$(CC) $(CFLAGS) -o $@ $<

lesson4_2: lesson4_2.c
	$(CC) $(CFLAGS) -o $@ $<

lesson4_3: lesson4_3.c
	$(CC) $(CFLAGS) -o $@ $<

lesson4_4: lesson4_4.c
	$(CC) $(CFLAGS) -o $@ $<

run1: lesson4_1
	./lesson4_1

clean:
	rm -f $(TARGETS)