CC=gcc
CFLAGS=-pthread
MAKE=make

all: client server

client:
	cd echo-client; $(MAKE)

server:
	cd echo-server; $(MAKE)
