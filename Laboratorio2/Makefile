CC=gcc
CFLAGS=
DEPS = Laboratorio1.h FileManager.h HashTable.h Tests.h Logger.h

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

Laboratorio1: main.o HashTable.o FileManager.o Tests.o Logger.o
	$(CC) -o laboratorio1 main.o HashTable.o FileManager.o Tests.o Logger.o
