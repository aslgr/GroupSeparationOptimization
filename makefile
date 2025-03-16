CFLAGS = -Wall -g # flags de compilacao
LDFLAGS = -lm

CC = gcc

# arquivos-objeto
	objects = separa.o TestaEntrada.o separaAux.o
     
all: separa.o TestaEntrada.o separaAux.o
	$(CC) -o separa separa.o TestaEntrada.o separaAux.o $(LDFLAGS)

TestaEntrada.o: TestaEntrada.c
	$(CC) -c $(CFLAGS) TestaEntrada.c

separaAux.o: separaAux.c
	$(CC) -c $(CFLAGS) separaAux.c

separa.o: separa.c
	$(CC) -c $(CFLAGS) separa.c

clean:
	rm -f $(objects) separa