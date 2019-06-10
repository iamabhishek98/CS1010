.SILENT: samplerun
CC=clang
LDLIBS=-lm -lcs1010
INCLUDEDIR=~cs1010/include
CFLAGS=-g -Wall -Wextra -Wpedantic -I $(INCLUDEDIR) -L $(LIBDIR)
LIBDIR=~cs1010/lib

all: selectionsort add mastermind samplerun

samplerun: 
	./test.sh selectionsort 3
	./test.sh add 5
	./test.sh mastermind 2

# vim:noexpandtab
