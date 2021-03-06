CC = gcc
CFLAGS = -lGL -lglut -lGLU -g -Wall -ansi -pedantic

#teste_ponto: general.o teste.o Defesa.o Tiro.o
#	$(CC) $(CFLAGS) $^ -lm -o $@

run: teste_nave
	./$^

teste_nave: teste_nave.h teste_nave.c Defesa.o Tiro.o general.o Nave.o Cenario.o
	$(CC) $^ -o $@ -lm  $(CFLAGS) 

Cenario.o: Cenario.c Cenario.h Defesa.h Tiro.h general.o general.h
	
	$(CC) -g -lm -c Cenario.c

Defesa.o: Defesa.c Defesa.h general.h Nave.h Tiro.h Cenario.h
	$(CC) -g -lm -c  Defesa.c

Nave.o: teste_nave.h teste_nave.c  Nave.c Nave.h general.h Tiro.h Cenario.h
	$(CC) -g -lm -c Nave.c

Tiro.o: Tiro.c Tiro.h general.h
	$(CC) -g -lm -c Tiro.c

general.o: general.c general.h
	$(CC)  -g -c general.c -lm

clean:
	rm -f *.o

