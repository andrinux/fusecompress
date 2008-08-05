CFLAGS  += $(CDEBUG) -D_REENTRANT -O2 -D_FILE_OFFSET_BITS=64 -Wall -D_POSIX_C_SOURCE=200112L -D_POSIX_SOURCE -D_SVID_SOURCE -D_BSD_SOURCE -D_XOPEN_SOURCE=500
LDFLAGS += $(LDEBUG) -lpthread -lfuse -lz -lbz2

all:
	@echo "specify \"make release\", \"make debug\""

help:
	@echo "specify \"make release\", \"make debug\""

%.d: %.c
	@set -e; rm -f $@; $(CC) -M $(CFLAGS) $< > $@.$$$$; sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; rm -f $@.$$$$

sources := $(wildcard *.c)
sources += minilzo/lzo.c minilzo/minilzo.c

objects := $(sources:.c=.o)
depends := $(sources:.c=.d)

-include $(depends)

debug: fusecompress
debug: CDEBUG=-DDEBUG -pg
debug: LDEBUG=-pg

release: fusecompress
release: CDEBUG=-DNDEBUG

fusecompress: $(objects)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $(objects)

clean:
	rm -f $(objects)
	rm -f $(depends)
	rm -f fusecompress
