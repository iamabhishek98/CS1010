.SILENT: samplerun
CC=clang
LDLIBS=-lm -lcs1010
INCLUDEDIR=~cs1010/include
CFLAGS=-g -Wall -Wextra -Wpedantic -I $(INCLUDEDIR) -L $(LIBDIR)
LIBDIR=~cs1010/lib

all: permutation1 permutation2 permutation3 samplerun

samplerun: 
	./test.sh permutation1 2
	./test.sh permutation2 2
	./test.sh permutation3 3

# vim:noexpandtab
