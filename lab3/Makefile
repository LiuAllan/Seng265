# Very simple Makefile that creates two exectuables (one which uses provided debug.h file)
# To run:
#      $ make all
#      $ make magic
#      $ make treasure 

CFLAGS =-Wall -g -std=c99
LIBS =-I.

all: hello treasure magic

hello: helloworld.c
	gcc $< -o $@  $(CFLAGS) $(LIBS)

treasure : treasure_map.c 
	gcc $< -o $@  $(CFLAGS) $(LIBS)

magic : magic_number.c 
	gcc $< -o $@  $(CFLAGS) $(LIBS)

clean:
	-rm -f hello treasure magic
