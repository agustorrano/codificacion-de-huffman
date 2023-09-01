# Makefile para comprimir y descomprimir archivos con el algoritmo de Huffman
# Escribiendo "make" en la terminal se genera el ejecutable del programa automáticamente
# Escribiendo "make tests" en la terminal se genera el ejecutable de los casos de prueba
# Para la compresión: ".\huff C f.txt"
# Para la descompresión: ".\huff D f.txt.hf"

CC = gcc
CFLAGS = -g -Wall -Wextra -Werror -std=c99
EXE.NAME = huff
FILES.O = io.o letra.o btree.o comprimir.o descomprimir.o

all: $(FILES.O)
		$(CC) -o $(EXE.NAME) $(FILES.O) main.c

.PHONY: all clean tests

tests:
	$(CC) -o tests $(FILES.O) tests.c

io.o: io.c
		$(CC) $(CFLAGS) -c io.c

letra.o: letra.c
		$(CC) $(CFLAGS) -c letra.c

btree.o: btree.c
		$(CC) $(CFLAGS) -c btree.c

comprimir.o: comprimir.c
		$(CC) $(CFLAGS) -c comprimir.c

descomprimir.o: descomprimir.c
		$(CC) $(CFLAGS) -c descomprimir.c


clean:
		rm -f huff
		rm -f *.o
