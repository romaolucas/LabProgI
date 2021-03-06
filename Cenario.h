#ifndef CENARIO_H_INCLUDED
#define CENARIO_H_INCLUDED
#include "general.h"
#include "Defesa.h"
#include "Tiro.h"

typedef struct nodeTiro nodeTiro;
typedef struct nodeDefense nodeDefense;

struct nodeTiro
{
  Tiro *tiro;
  nodeTiro *next;
} ;

struct nodeDefense
{
  Defense *defense;
  nodeDefense *next;
} ;

/*Inicializa o cenario e as duas listas ligadas*/
void initCenario();

/*Recebe o tiro já pronto, uma vez que ele é gerado
por tiro.c/defesa.c e não aleatoriamente*/
void includeTiro(Tiro *tiro);

/*Recebe os parâmetros gerados aleatoriamente, cria as structs
(ponto, defense) e inclui na lista*/
void includeDefense(Defense *d);

void imprimeCenario();

/*Libera todas as defesas, tiros e as listas ligadas*/
void freeCenario();

void freeListaTiros();

void freeListaDefesas();

void createDefense();

int update();

extern nodeTiro *tiroList;
extern nodeDefense *defenseList;

#endif
