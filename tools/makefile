CMD=pfscreate pfsadd pfslist pfsdel

CC=gcc
CFLAGS=-std=c99

all: $(CMD)

pfscreate: pfscreate.c pfs.o
	$(CC) $(CFLAGS) $^ -o $@

pfsadd: pfsadd.c pfs.o
	$(CC) $(CFLAGS) $^ -o $@

pfsdel: pfsdel.c pfs.o
	$(CC) $(CFLAGS) $^ -o $@

pfslist: pfslist.c pfs.o
	$(CC) $(CFLAGS) $^ -o $@

pfs.o: pfs.c pfs.h const.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o
	rm -f *.img
	rm -f $(CMD)
	rm -f shell
