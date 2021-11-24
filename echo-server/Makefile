CC=gcc
LIBS=-pthread
TARGET=echo-server
OBJS=echo-server.o

$(TARGET): $(OBJS)
	$(CC) $(LIBS) -o $@ $^

$(OBJS): $(TARGET).c
	$(CC) $(LIBS) -c -o $@ $^

clean:
	rm -f $(TARGET) *.o
