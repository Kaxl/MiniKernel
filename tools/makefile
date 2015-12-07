CMD=pfscreate pfsadd pfslist pfsdel

all: $(CMD)

pfscreate: pfscreate.c
	gcc $< -o $@

pfsadd: pfsadd.c
	gcc $< -o $@

pfslist: pfslist.c
	gcc $< -o $@

clean:
	rm -f *.o
	rm -f *.img
	rm -f $(CMD)
