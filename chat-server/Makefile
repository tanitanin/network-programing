# echo server programing

# directory
SRCDIR = src
BINDIR = bin
INCDIR = -I./$(SRCDIR) \
         
LIBDIR = -L./$(SRCDIR) \
         -L/usr/lib64 \
         -L/usr/local/lib64 \

LDFLAGS = -lpthread\
          -lboost_system\

# files
MAIN_OBJ = $(sort \
            $(patsubst %.c,%.o,$(wildcard *.c)) \
            $(patsubst %.cc,%.o,$(wildcard *.cc)) \
            $(patsubst %.c,%.o,$(wildcard $(SRCDIR)/*.c)) \
            $(patsubst %.cc,%.o,$(wildcard $(SRCDIR)/*.cc))) \

# commands
CC = gcc
CFLAGS = $(INCDIR) $(LIBDIR) -O2 -Wall $(LDFLAGS)
CXX = g++
CXXFLAGS = $(INCDIR) $(LIBDIR) -O2 -Wall $(LDFLAGS)

# suffix rule
.SUFFIXES: .c .cc .h .o
.c.o:
	$(CC) $(CFLAGS) -o $@ -c $<
.cc.o:
	$(CXX) $(CXXFLAGS) -o $@ -c $<

# dependance

# target
.PHONY: all
all: server

.PHONY: run
run: server-run

server: $(MAIN_OBJ)
	$(CXX) $(CXXFLAGS) $^ -o $(BINDIR)/$@

server-run:
	./$(BINDIR)/server

.PHONY: clean
clean:
	rm -f $(SRCDIR)/*.o $(BINDIR)/*

