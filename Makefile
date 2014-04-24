teste_ponto: general.o teste.o
	gcc $^ -lm -o $@

general.o:
	gcc general.c -lm -c -o $@ 

teste.o:
	gcc teste.c -lm -c -o $@ 