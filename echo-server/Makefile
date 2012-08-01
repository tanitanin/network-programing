# echo server programing

# directory
SRCDIR = src
BINDIR = bin

#
CC = gcc
CFLAGS = -Wall -lpthread

#
$(BINDIR)/server: $(SRCDIR)/main.o
	$(CC) $(CFLAGS) $< -o $@

$(BINDIR)/client: $(SRCDIR)/client.o
	$(CC) $(CFLAGS) $< -o $@

# target
all: server

run: server-run

server: $(BINDIR)/server

server-run:
	./bin/server

client: $(BINDIR)/client
	./bin/client

clean:
	@rm $(SRCDIr)/*.o $(BINDIR)/*

