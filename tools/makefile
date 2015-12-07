CMD=pfscreate pfsadd pfslist pfsdel

all: $(CMD)

pfscreate: pfscreate.c
	gcc $< -o $@

pfsadd: pfsadd.c
	gcc $< -o $@

clean:
	rm -f *.o
	rm -f $(CMD)
