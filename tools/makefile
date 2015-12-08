CMD=pfscreate pfsadd pfslist pfsdel

all: $(CMD)

pfscreate: pfscreate.c pfs.o
	gcc $^ -o $@

pfsadd: pfsadd.c pfs.o
	gcc $^ -o $@

pfslist: pfslist.c pfs.o
	gcc $^ -o $@

pfs.o: pfs.c pfs.h
	gcc -c $< -o $@

clean:
	rm -f *.o
	rm -f *.img
	rm -f $(CMD)
