CC=gcc
CFLAGS=-I.
DEPS=hellomake.h
OBJ=hellomake.o hellofunc.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

hellomake.exe: $(OBJ)
	$(CC) -o $@ $^
