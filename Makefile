CC=gcc
CFLAGS=-Wall -Werror -Wextra -pedantic -std=c99
LDLIBS=-lasan
LDFLAGS=-fsanitize=address
SRCS=$(wildcard *.c)
OBJS=$(patsubst %.c,%.o,$(SRCS))

all: app app.exe

app: $(OBJS)
	$(CC) $(LDLIBS) $(LDFLAGS) -o $@ $^

app.exe: $(OBJS)
	x86_64-w64-mingw32-gcc $(LDLIBS) $(LDFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm *.o *.raw

extraclean:
	rm *.o *.raw app out.wav

view: out.wav
	audacity $^ &

out.wav: out.raw
	ffmpeg -f f32le -ar 44.1k -ac 1 -c:a pcm_f32le -i $^ $@

out.raw: app
	./app
