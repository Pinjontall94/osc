CC=gcc
CFLAGS=-Wall -Werror -Wextra -pedantic -std=c99
LDLIBS=-lasan
LDFLAGS=-fsanitize=address
SRCS=$(wildcard *.c)
OBJS=$(patsubst %.c,%.o,$(SRCS))

all: out.wav

out.wav: out.raw
	ffmpeg -f f32le -ar 44.1k -ac 1 -c:a pcm_f32le -i $^ $@

out.raw: app
	./app

app: $(OBJS)
	$(CC) $(LDLIBS) $(LDFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm *.o *.raw

extraclean:
	rm *.o *.raw app out.wav

view:
	audacity out.wav &
