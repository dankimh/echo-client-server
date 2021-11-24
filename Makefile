CC=gcc
CFLAGS=-pthread
MAKE=make

all: client server

client:
	cd echo-client; $(MAKE)

server:
	cd echo-server; $(MAKE)

clean: clean-client clean-server

clean-client: 
	cd echo-client; $(MAKE) clean

clean-server:
	cd echo-server; $(MAKE) clean
