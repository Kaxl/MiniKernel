CMD=pfscreate pfsadd sfslist sfsdel

all: $(CMD)

pfscreate: pfscreate.c
	gcc $< -o $@

clean: 
	rm -f *.o
	rm -f $(CMD)
