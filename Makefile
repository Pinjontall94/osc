CC=gcc
CFLAGS=-Wall -Werror -std=c99 -I. -I./include
LDLIBS=-lasan 
LDFLAGS=-L/usr/local/include -fsanitize=address


.PHONY: all
all: app

app: app.o
	$(CC) $(LDLIBS) $(LDFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

.PHONY: clean
clean:
	rm app *.o

.PHONY: run
run:
	./app
