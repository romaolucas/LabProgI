CC = gcc
CFLAGS = -g -Wall -ansi -pedantic

#teste_ponto: general.o teste.o Defesa.o Tiro.o
#	$(CC) $(CFLAGS) $^ -lm -o $@

teste: teste.c Defesa.o Tiro.o general.o Nave.o Cenario.o
	$(CC) $(CFLAGS) $^ -o $@ -lm

Cenario.o: Cenario.c Cenario.h Defesa.h Tiro.h general.o general.h
	
	$(CC) -g -lm -c Cenario.c

Defesa.o: Defesa.c Defesa.h general.h Nave.h Tiro.h Cenario.h
	$(CC) -g -lm -c  Defesa.c

Nave.o: Nave.c Nave.h general.h Tiro.h Cenario.h
	$(CC) -g -lm -c Nave.c

Tiro.o: Tiro.c Tiro.h general.h
	$(CC) -g -lm -c Tiro.c

general.o: general.c general.h
	$(CC)  -g -c general.c -lm

clean:
	rm -f *.o

