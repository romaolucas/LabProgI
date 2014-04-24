CC = gcc
CFLAGS = -g -Wall -ansi -pedantic

#teste_ponto: general.o teste.o Defesa.o Tiro.o
#	$(CC) $(CFLAGS) $^ -lm -o $@

teste: teste.c Defesa.o Tiro.o general.o
	$(CC) $(CFLAGS) $^ -o $@ -lm

Defesa.o: Defesa.c Defesa.h general.h Tiro.h
	$(CC) -lm -c  Defesa.c

Tiro.o: Tiro.c Tiro.h general.h
	$(CC) -lm -c Tiro.c

general.o:
	$(CC)  general.c -c -o $@ -lm

clean:
	rm -f *.o

