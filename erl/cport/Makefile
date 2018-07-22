ERL_LIB=/usr/lib/erlang/lib/erl_interface-3.6.4/
CFLAGS=-Wall -I/usr/local/include -I$(ERL_LIB)/include
LDFLAGS=-L. -L$(ERL_LIB)/lib 

sockrx : sockrx.c
	gcc $(LDFLAGS) sockrx.c -lerl_interface -lei -lpthread -lpcap -o sockrx

socktx : socktx.c
	gcc $(LDFLAGS) socktx.c -lerl_interface -lei -lpthread -lpcap -o socktx

all : sockrx.c socktx.c
	gcc $(LDFLAGS) sockrx.c -lerl_interface -lei -lpthread -lpcap -o sockrx
	gcc $(LDFLAGS) socktx.c -lerl_interface -lei -lpthread -lpcap -o socktx

clean :
	rm sockrx socktx
