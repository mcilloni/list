ifndef CC
	CC=clang
endif

ifndef AR
	AR=ar 
endif

ifndef RANLIB
	RANLIB=ranlib
endif

ARCH = $(shell uname -m)
UNAME = $(shell uname)

FLAGS =

ifeq ($(ARCH),x86_64)
ifeq (,$(findstring CYGWIN,$(UNAME)))
	FLAGS += -fPIC
endif
endif

.PHONY: all,clean

SRCS = $(wildcard *.c)
OBJS = $(patsubst %.c,%.o,$(SRCS))

all: $(OBJS)
	$(AR) rc liblist.a list.o pool.o
	$(RANLIB) liblist.a
	$(CC) -o allocex allocex.c -std=c99 -L. -llist  -Wall -pedantic -g
	$(CC) -o ex ex.c -std=c99 -L. -llist  -Wall -pedantic -g
	$(CC) -o poolex poolex.c -std=c99 -L. -llist  -Wall -pedantic -g
	$(CC) -o slicex slicex.c -std=c99 -L. -llist  -Wall -pedantic -g
	$(CC) -o strex strex.c -std=c99 -L. -llist  -Wall -pedantic -g
	rm -f *.o

%.o: %.c
	$(CC) -c $< -o $@ -std=c99 -g -Wall -pedantic $(FLAGS)

clean:
	rm -f liblist.a
	rm -f $(OBJS)
	rm -f ex strex allocex slicex poolex

