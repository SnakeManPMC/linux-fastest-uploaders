#
# Fastest Uploaders for DayDream linux (c) PMC
#
# Remember to change this to the dir where your DD-source lives!
DDSRC = /upload1/dd/bbs

# no need to change more below.
CC=		gcc
CFLAGS=		-O2
LIBS=		-L$(DDSRC)/lib/ -I$(DDSRC)/main/ -I$(DDSRC)/lib/ -I/upload1/code/include/

all:		fastest fast log

fastest:        fastest.c
		$(CC) $(CFLAGS) $(LIBS) -o $@ $< -ldd

fast:		fast.c
		$(CC) -o $@ $<

log:            log.c
	        $(CC) -o $@ $<
