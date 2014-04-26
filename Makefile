CC = gcc
CFLAGS = -g -Wall -ansi -pedantic

#teste_ponto: general.o teste.o Defesa.o Tiro.o
#	$(CC) $(CFLAGS) $^ -lm -o $@

teste: teste.c Defesa.o Tiro.o general.o Nave.o Cenario.o
	$(CC) $(CFLAGS) $^ -o $@ -lm

Cenario.o: Cenario.c Cenario.h Defesa.h Tiro.h general.h
	$(CC) -lm -c Cenario.c

Defesa.o: Defesa.c Defesa.h general.h Tiro.h
	$(CC) -lm -c  Defesa.c

Nave.o: Nave.c Nave.h general.h Tiro.h
	$(CC) -c Nave.c

Tiro.o: Tiro.c Tiro.h general.h
	$(CC) -lm -c Tiro.c

general.o:
	$(CC)  general.c -c -o $@ -lm

clean:
	rm -f *.o

