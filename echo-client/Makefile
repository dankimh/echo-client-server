CC=gcc
LIBS=-pthread
TARGET=echo-client
OBJS=echo-client.o

$(TARGET): $(OBJS)
	$(CC) $(LIBS) -o $@ $^

$(OBJS): $(TARGET).c
	$(CC) $(LIBS) -c -o $@ $^

clean:
	rm -f $(TARGET) *.o
