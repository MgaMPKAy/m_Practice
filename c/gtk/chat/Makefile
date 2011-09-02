LIBS=`pkg-config --libs gtk+-2.0 glib-2.0`
INCS=`pkg-config --cflags gtk+-2.0 glib-2.0`

QUIET_CC=@echo '  CC     '$@;
QUIET_LD=@echo '  CCLD   '$@;	
QUIET_RM=@echo '  RM     '$@;

.c.o:
	$(QUIET_CC)$(CC) -g -Wall --std=c99 $(CFLAGS) $(INCS) -c $*.c

all: chat-server gtk-chat-server-test

chat-server: chat-server.o
	$(QUIET_LD)$(CC) -g -Wall --std=c99 $(CFLAGS) -o $@ $< -lm $(LIBS)
gtk-chat-server-test: gtk-chat-server-test.o
	$(QUIET_LD)$(CC) -g -Wall --std=c99 $(CFLAGS) -o $@ $< -lm $(LIBS)
clean:
	@rm -fr *.o all
