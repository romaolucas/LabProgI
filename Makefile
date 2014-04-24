CC = gcc
CFLAGS = -lm -g -Wall -ansi -pedantic

teste_ponto: general.o teste.o Defesa.o
	$(CC) $(CFLAGS) $^ -lm -o $@

Defesa.o: Defesa.c Defesa.h general.h
	$(CC) -lm -c  Defesa.c

general.o:
	gcc general.c -c -o $@ 

teste.o:
	gcc teste.c -c -o $@


