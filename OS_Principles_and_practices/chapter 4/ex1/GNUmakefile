BINARIES :=  threadHello
all: $(BINARIES)

CFLAGS := $(CFLAGS) -g -Wall -Werror -D_POSIX_THREAD_SEMANTICS

CTHREADLIBS := thread.o

clean:
	rm -f *.o $(BINARIES)

tags:
	etags *.h *.c

%.o: %.c
	gcc -c $(CFLAGS) $< -o $@

threadHello: threadHello.c $(CTHREADLIBS)
	gcc -pthread $(CFLAGS) $^ -o $@

