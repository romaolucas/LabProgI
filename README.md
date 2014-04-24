LabProgI
========

Antonio (24/04/2014 - 01:56)
============================

Adicionei general.c e general.h
  - Criei a estrutura Point, pra não ter que ficar fazendo infinitos ints
  - Criei função initPoint, que inicializa a struct point
  - Criei uma função generica pra calcular a distância entre dois pontos
  (fiz um pequeno programa pra testar essas duas funções, só dar make)

Adicionei Tiro.h e Tiro.c
   - Criei a estrutura Tiro
   - Criei função initTiro que inicializa a struct tiro
   - Criei freeTiro, pra liberar a struct tiro e as structs internas

Modifiquei Defesa.h e Defesa.c
   - Criei o tipo TIRO_TIPO (por enquanto só tem NORMAL, depois da pra adicionar outros tipos
     de tiro)
   - Troquei o int x, int y, int z por uma struct Point
   - Criei a função freeDefesa (antes não precisava, mas agora tem uma struct interna)
   - Mudei algumas coisas dentro das funções (em C não dá pra fazer uma função que recebe
     ou retorna uma struct, só ponteiros)

-----------------------------------------------------------------------------------------------------
