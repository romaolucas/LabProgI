#include <stdlib.h>
#include <stdio.h>
#include "general.h"
#include "Cenario.h"
#include "Defesa.h"
#include "Tiro.h"
#include "Nave.h"

nodeTiro *tiroList;
static nodeDefense *defenseList;
static boolean init = FALSE;
static float maxDefense = 0;
static int N = 0;

/*Essas serão as cabeças, não vai ter nenhum tiro ou defesa associado a elas*/
void initCenario()
{
  tiroList = mallocSafe(sizeof(nodeTiro));
  defenseList = mallocSafe(sizeof(nodeDefense));
  /*Incluir aqui depois a parte em que o cenario é gerado aleatoriamente*/
  init = TRUE;
}

void includeDefense(Defense *d)
{
  /*Se não estiver inicializado*/
  if(init == FALSE)
  {
    printf("ERRO: tentativa de incluir defesa sem inicializar listas\n");
    return;
  }
  nodeDefense *corredor = defenseList;
  while (corredor->next != NULL)
    corredor = corredor->next;
  /*corredor->next é null agora*/
  corredor->next = mallocSafe(sizeof(nodeDefense));
  corredor->next->defense = d;
  N++;
}

void includeTiro(Tiro *t)
{
  if(init == FALSE)
  {
    printf("ERRO: tentativa de incluir tiro sem inicializar listas\n");
    return;
  }
  nodeTiro *corredor  = tiroList;
  while(corredor->next != NULL)
    corredor = corredor->next;
  /*Corredor->next é null agora*/
  corredor->next = mallocSafe(sizeof(nodeTiro));
  corredor->next->tiro = t;
}

void imprimeCenario() {
   nodeDefense *p = defenseList->next;
   nodeTiro *q = tiroList->next;
   Point *c;
   printf("Nave na posicao (%4.2f, %4.2f, %4.2f)\n", ship->position->x, ship->position->y, ship->position->z);
   while (p != NULL) {
      c = p->defense->position;
      printf("Posicao (%4.2f, %4.2f, %4.2f)\n hp: %d\n", c->x, c->y, c->z, p->defense->hp);
      p = p->next;
   }
}

void freeCenario()
{
  if (init == FALSE)
    return;     
  freeListaTiros();
  freeListaDefesas();
}

void freeListaTiros()
{
  nodeTiro *corredor = tiroList;
  nodeTiro *proximo = corredor->next;
  while(proximo != NULL)
  {
    freeTiro(corredor->tiro);
    free(corredor);
    corredor = proximo;
    proximo = proximo->next;
  }
  /*Na última vez, o proximo vai chegar a NULL e o corredor não vai ser liberado.
    Para evitar isso, no final adicionamos:*/
  freeTiro(corredor->tiro);
  free(corredor);
}

void freeListaDefesas()
{
  nodeDefense *corredor = defenseList;
  nodeDefense *proximo = corredor->next;
  while(proximo != NULL)
  {
    freeDefense(corredor->defense);
    free(corredor);
    corredor = proximo;
    proximo = proximo->next;
  }
  /*Aplica-se a mesma lógica do anterior*/
  freeDefense(corredor->defense);
  free(corredor);
  N = 0;
}

void createDefense() {
   Point *p;
   if (N < (int) maxDefense) {
      p = mallocSafe(sizeof(Point));
      p->x = RandomNumber(0.0, 500.0);
      p->y = RandomNumber(0.0, 600.0);
      p->z = RandomNumber(ship->position->z, 1000.0 + ship->position->z);
      includeDefense(initDefense(p, DEFAULT_HP, NORMAL)); 
   }
}

int update() {
   int fim;
   Point *p;
   nodeDefense *d;
   nodeDefense *a;
   nodeTiro *at;
   nodeTiro *t;

   /*primeiramente, se nao tem mais vidas, game over, flag pra indicar que deve-se 
   dar update/draw em outra coisa que nao o jogo em andamento
   if (ship->vidas == 0) gameOver = TRUE;*/

   /*Atualiza nave (nova posicao, checa colisoes e atualiza hp se necessario) */
   fim = updateShip();

   /*Atualiza posições. Essas funções estão em Tiro.c, Defesa.c, Nave.c*/
   at = tiroList;
   t = at->next;
   while (t != NULL)
   {
     boolean out;
     out = updateTiro(t->tiro);
     /*Precisa fazer isso pra não estragar a lista ligada quando for tirar*/
     if (out){
         at->next = t->next;
         freeTiro(t->tiro);
         free(t);
         t = at->next;
     }
     at = t;
     if (t != NULL)
        t = t->next;
   }

   /*loop para atualizar as defesas*/
   a = defenseList;
   d = a->next;
   while (d != NULL)
   {
     boolean test;
     test = updateDefense(d->defense);
     if (test || isDefenseDestroyed(d->defense)){
        a->next = d->next;
        freeDefense(d->defense);
        free(d);
        d = a->next;
     }
     a = d;
     if (d != NULL)
        d = d->next;   
   }

   /*Cria nova defesa, se necessário*/
   createDefense();
   /*A fazer - cria novo tiro, se necessário*/
   return fim;
}

