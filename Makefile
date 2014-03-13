ifndef CC
	CC=clang
endif

AR=ar
RANLIB=ranlib

all: clean
	$(CC) -c list.c -std=c11 -g -Wall -pedantic -fPIC
	$(AR) -rc liblist.a list.o
	$(RANLIB) liblist.a
	$(CC) -o ex ex.c -std=c11 -L. -llist  -Wall -pedantic -g
	$(CC) -o strex strex.c -std=c11 -L. -llist  -Wall -pedantic -g
	$(CC) -o allocex allocex.c -std=c11 -L. -llist  -Wall -pedantic -g
	$(CC) -o slicex slicex.c -std=c11 -L. -llist  -Wall -pedantic -g
	rm -f *.o

clean:
	rm -f liblist.a
	rm -f *.o
	rm -f ex strex allocex slicex

